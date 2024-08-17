## 1. Mod Scaffolding
This first DLL example demonstrates creating a simple DLL mod for [REPENTOGON](https://repentogon.com/). In this example, we register a boolean variable that will be available in Lua.

## Code Overview
```cpp
#include <lua.hpp>
#include "LuaCore.h"
#include "IsaacRepentance.h"
#include "HookSystem.h"

HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
    super();

    lua_State* L = _state;
    lua::LuaStackProtector protector(L);

    lua_pushboolean(L, true);
    lua_setglobal(L, "_EXAMPLE_MOD_LOADED");
}
```

We start with the minimum necessary includes required to make the mod work. After that, we use HOOK_METHOD to add a custom boolean variable named _EXAMPLE_MOD_LOADED into Lua.

#### HOOK_METHOD
HOOK_METHOD is a method provided by REPENTOGON to hook into various systems within The Binding of Isaac. Conceptually, it is similar to the ModCallback system available for modding in TBOI Lua, but it offers deeper integration into the underlying system than you can achieve with Lua alone.

The definition for this method is: HOOK_METHOD(_classname, _name, _type)

In this mod's code, we are hooking into the LuaEngine::RegisterClasses functionality. As part of our hook, we first call super() to invoke the original method before injecting our code into the process. It is important to call super() to ensure that the original class functionality we are hooking into is executed. We have the option of placing super() either before or after our custom code; in this case, we place it as the first line in our function.

Next, we initialize L as a reference to the current Lua instance state. We also add the LuaStackProtector. Whenever we modify the Lua stack, we should start with this protector.

Finally, we add the custom functionality. On line 12, we push a boolean true value onto the stack. On line 13, we set a new global variable named _EXAMPLE_MOD_LOADED with the value from the boolean true we pushed onto the stack.

## Building
Follow the standard build process from the root of this repository.
![01_mod_scaffolding_cmake](/_images/01_mod_scaffolding_cmake.png)

## Testing
Once you have added the newly generated DLL to the Isaac Directory (or had CMake do that for you automatically), start Isaac. In the Debug Console, you can enter:
```
lua print(_EXAMPLE_MOD_LOADED and "True" or "False")
```
If the mod was loaded successfully, you should see the following in your console:
![01_mod_scaffolding](/_images/01_mod_scaffolding.png)

