## 4. Calling Lua
In this mod, we will be calling Lua methods from our C++ code. We add a generic wrapper to make calling the Isaac/REPENTOGON API really straight forward.

## Code Overview
At this point, the REPENTOGON specific code should be straight forward to understand from the previous methods. The code will have inline comments where
applicable to help understand what is going on; however, for the most part this will be a standalone example.

## Building
Follow the standard build process from the root of this repository.
![03_static_class_cmake](/_images/04_calling_lua_cmake.png)

## Testing
Once you have added the newly generated DLL to the Isaac Directory (or had CMake do that for you automatically), start Isaac. When you pickup any coins, a notification
will be displayed at the top of the screen.

![03_static_class](/_images/04_calling_lua.png)

