#include <lua.hpp>
#include "LuaCore.h"
#include "IsaacRepentance.h"
#include "HookSystem.h"

enum Colors : unsigned int
{
	Green = 4278222848U,
	Red = 4294901760U,
	Yellow = 4294967040U,
};

LUA_FUNCTION(Lua_Hello_World) {
	g_Game->GetConsole()->Print("Hello World!\n", Console::Color::WHITE, 0x96U);
	g_Game->GetConsole()->Print("Hello World!\n", Colors::Green, 0x96U);
	g_Game->GetConsole()->Print("Hello World!\n", Colors::Red, 0x96U);
	g_Game->GetConsole()->Print("Hello World!\n", Colors::Yellow, 0x96U);
	return 0;
}

HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();

	lua_State* L = _state;
	lua::LuaStackProtector protector(L);

	lua_pushcfunction(L, Lua_Hello_World);
	lua_setglobal(L, "HelloWorld");
}
