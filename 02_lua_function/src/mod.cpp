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
