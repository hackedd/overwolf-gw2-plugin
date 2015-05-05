/*
    Overwolf GW2 Plugin
    Copyright (c) 2014 Ovefwolf Ltd.
*/
#include "Thread.h"

using namespace utils;

const DWORD kStopThreadTimeoutMS = 10000;

Thread::Thread() : thread(nullptr), stopping(false) {
}

Thread::~Thread() {
}

bool Thread::Start() {
    if (nullptr != thread) {
        return false;
    }

    if (!CreateEvents()) {
        return false;
    }

    ClearQueue();

    stopping = false;

    thread = CreateThread(nullptr, 0, ThreadProc, (LPVOID) this, 0, nullptr);
    return thread != nullptr;
}

bool Thread::Stop() {
    if (thread == nullptr) {
        return true;
    }

    {
        CriticalSectionLock lock(queue_critical_section);
        stopping = true;
    }

    SetEvent(events[EVENT_STOP]);
    bool ret = WaitForSingleObject(thread, kStopThreadTimeoutMS) == WAIT_OBJECT_0;
    DestroyEvents();
    return ret;
}

bool Thread::PostTask(Task task_func) {
    CriticalSectionLock lock(queue_critical_section);

    if (thread == nullptr) {
        return false;
    }

    if (stopping) {
        return false;
    }

    task_queue.push(task_func);

    return (TRUE == SetEvent(events[EVENT_NEW_TASK]));
}

bool Thread::CreateEvents() {
    events[EVENT_STOP] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    events[EVENT_NEW_TASK] = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    for (int i = 0; i < EVENTS_COUNT; i++) {
        if (events == nullptr) {
            return false;
        }
    }

    return true;
}

void Thread::DestroyEvents() {
    for (int i = 0; i < EVENTS_COUNT; i++) {
        if (events[i] != nullptr) {
            CloseHandle(events[i]);
            events[i] = nullptr;
        }
    }
}

void Thread::ClearQueue() {
    CriticalSectionLock lock(queue_critical_section);

    TaskQueue empty_queue;
    std::swap(task_queue, empty_queue);
}

void Thread::HandleNewTaskEvent() {
    while (!task_queue.empty()) {
        Task task;

        {
            CriticalSectionLock lock(queue_critical_section);

            // don't continue processing messages if we are stopping
            if (stopping) {
                return;
            }

            task = task_queue.front();
            task_queue.pop();
        }

        if (!task._Empty()) {
            task();
        }
    }
}

DWORD WINAPI Thread::ThreadProc(IN LPVOID lpParameter) {
    Thread* p_thread_queue = (Thread*)lpParameter;

    if (lpParameter == nullptr) {
        return 0;
    }

    bool continue_running = true;
    int event_index;

    while (continue_running) {
        DWORD wait = WaitForMultipleObjectsEx(EVENTS_COUNT, p_thread_queue->events, FALSE, INFINITE, TRUE);

        event_index = (wait - WAIT_OBJECT_0);

        // check if we are to be stopped
        if (EVENT_STOP == event_index || event_index < 0 || event_index > EVENTS_COUNT) {
            continue_running = false;
        } else {
            // new task
            p_thread_queue->HandleNewTaskEvent();
        }
    }

    p_thread_queue->ClearQueue();
    p_thread_queue->thread = nullptr;

    return 0;
}
