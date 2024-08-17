## 2. Lua Function
In this mod, we will be introducing a Lua global function, that will print output to the Console.

## Code Overview
```cpp
#include <lua.hpp>
#include "LuaCore.h"
#include "IsaacRepentance.h"
#include "HookSystem.h"

LUA_FUNCTION(Lua_Hello_World) {
	g_Game->GetConsole()->Print("Hello World!\n", Console::Color::WHITE, 0x96U);
	return 0;
}

HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();

	lua_State* L = _state;
	lua::LuaStackProtector protector(L);

	lua_pushcfunction(L, Lua_Hello_World);
	lua_setglobal(L, "HelloWorld");
}
```

See previous example mods for information about HOOK_METHOD.

#### LUA_FUNCTION
In this mod, we are introducing the LUA_FUNCTION method from REPENTOGON. This will allow you to define a function that can be used in Lua. We then register this function as a global in our HOOK_METHOD.

When we define our LUA_FUNCTION, we arre giving it a C Function name of Lua_Hello_World.

The contents of the the LUA_FUNCTION is pretty straight-forward. We first grab the g_Game global that will allow us to get the reference to the Console - from there we can print a message to the console.

The `return 0;` is important to note. When a Lua function returns, the results are pushed onto the stack in direct order, with the last result being on top after the call. The return integer used in LUA_FUNCTION is specifying the number of returned elements on the stack - in this case, we are not returning anything, since nothing was pushed on to the stack. In the 03. Static Class example mod we will introduce returning data from a LUA_FUNCTION.

Finally, in our HOOK_METHOD, we are pushing the C Function name of the LUA_FUNCTION to the stack, and then, just like the first DLL example, we set it as a global. This will now allow "HelloWorld()" to be called from Lua.

## Building
Follow the standard build process from the root of this repository.
![02_lua_function_cmake](/_images/02_lua_function_cmake.png)

## Testing
Once you have added the newly generated DLL to the Isaac Directory (or had CMake do that for you automatically), start Isaac. In the Debug Console, you can enter:
```
lua HelloWorld()
```
If the mod was loaded successfully, you should see the following in your console:
![02_lua_function](/_images/02_lua_function.png)

