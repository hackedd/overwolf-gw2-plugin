/*
  Overwolf GW2 Plugin
  Copyright (c) 2014 Ovefwolf Ltd.
*/
#ifndef UTILS_THREAD_H_
#define UTILS_THREAD_H_

#include <queue>
#include <functional>
#include <Windows.h>
#include "CriticalSectionLock.h"

namespace utils {

class Thread {
public:
    typedef std::function<void()> Task;

    Thread();
    virtual ~Thread();

public:
    bool Start();
    bool Stop();
    bool PostTask(Task task_func);

private:
    bool CreateEvents();
    void DestroyEvents();
    void ClearQueue();
    void HandleNewTaskEvent();

    static DWORD WINAPI ThreadProc(IN LPVOID lpParameter);

    enum ThreadEvents {
        EVENT_STOP = 0,
        EVENT_NEW_TASK,
        EVENTS_COUNT
    };

    // contains two events - one for connecting each pipe
    // and one to stop the server
    HANDLE events[EVENTS_COUNT];

    // thread running the server
    HANDLE thread;

    bool stopping;

    typedef std::queue<Task> TaskQueue;
    TaskQueue task_queue;

    CriticalSection queue_critical_section;
};

};

#endif
