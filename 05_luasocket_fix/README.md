# 5. LuaSocket Fix
In this example, we are making creating a patch that includes a newer version of LuaSocket that is built against the REPENTOGON Lua5.4 build.

## Code Overview
This mode makes changes to both the mod.cpp, but, also the CMakeLists.txt. In the build process, we want to build LuaSocket 3.1.0 as part of
our mod code. Meanwhile, the mod.cpp source example is very straight forward, as it simply writes over the preloaded module reference of socket.core
with our newer version.

_Note_: As of writing, 8/21/2024, if one attempts to `require("socket")` in REPENTOGON, it will crash. This is because the existing luasocket is
built for Lua 5.1. This code will fix this issue, however for future readers, this may no longer be a fix that is necessary - but the code sample
still stands for how to inject a library in to the lua preload.

## Building
Follow the standard build process from the root of this repository.
![05_luasocket_fix_cmake](/_images/05_luasocket_fix_cmake.png)

## Testing
Once you have added the newly generated DLL to the Isaac Directory (or had CMake do that for you automatically), start Isaac. In the Debug Console, you can enter:
```
lua local s = require("socket"); print(s._VERSION);
```
If the mod was loaded successfully, you should see the following in your console:
![05_luasocket_fix](/_images/05_luasocket_fix.png)

