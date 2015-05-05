Overwolf Guild Wars 2 Mumble Link Plugin
========================================

This is a plugin that allows an Overwolf WebApp to read information from the (Guild Wars 2) Mumble link.

Building
--------

To build this plugin, you'll need the [Gecko SDK](gecko-sdk), also known as the XULRunner SDK. The plugin was successfully tested using the version for Gecko 1.9.2 (Firefox 3.6).

Unzip the xulrunner-sdk folder side-by-side with the OverwolfGW2Plugin folder (or create a symlink) - the project references this folder (see Additional Include Directories).

NOTE: we make sure to compile the plugin /MT so there are no dependencies on the C runtime libraries.

Using the Plugin
----------------

To use the plugin, place the `npOverwolfGW2Plugin.dll` in the directory of you WebApp. Then, add this to the `data` section of your manifest.json:

```json
    "plugins": [
      "npOverwolfGW2Plugin.dll"
    ]
```

And add an embed tag to your HTML:

```html
    <embed id="plugin" type="application/x-overwolf-gw2-plugin" width="0" height="0">
    </embed>
```

The plugin exposes the fields of the Mumble link as properties, which can be read from your app:

```javascript
    var plugin = document.getElementById("plugin");
    if (plugin.name == "Guild Wars 2") {
        console.log(plugin.identity);
    } else {
        console.log("Guild Wars 2 not running?");
    }
```

The following properties are implemented. Note that most of the properties are described on the [Mumble Wiki](mumble-link) or [Guild Wars 2 forum](gw2-link). The coordinate type has properties `x`, `y` and `z`.

Name            | Type       | Notes
--------------- | ---------- | -----
uiVersion       | number     | `2`
uiTick          | number     | Counter, incremented every frame (but not during cut-scenes).
fAvatarPosition | coordinate | Player position.
fAvatarFront    | coordinate | Unit vector pointing out of the players eyes.
fAvatarTop      | coordinate | Unit vector pointing out of the top of the player's head (always zeros).
name            | string     | `Guild Wars 2`
fCameraPosition | coordinate | Camera position.
fCameraFront    | coordinate | See `fAvatarFront`.
fCameraTop      | coordinate | See `fAvatarTop` (always zeros).
identity        | string     | Character identity, as a JSON string.
serverAddress   | string     | The server address, formatted as a string (same IP as displayed using the `/ip` command in-game).
mapId           | number     | [Map Id][maps]
mapType         | number     | [Map Type][map-type]
shardId         | number     | Shard Id
instance        | number     | Instance
buildId         | number     | [Game Version][build]
description     | string     | Empty.

[gecko-sdk]: https://developer.mozilla.org/en/docs/Gecko_SDK
[mumble-link]: http://wiki.mumble.info/wiki/Link
[gw2-link]: https://forum-en.guildwars2.com/forum/community/api/GW2-s-Mumble-Link-context-data-format/2388565
[map-type]: https://forum-en.guildwars2.com/forum/community/api/GW2-s-Mumble-Link-context-data-format/4482365
[maps]: https://api.guildwars2.com/v2/maps
[build]: https://api.guildwars2.com/v2/build
