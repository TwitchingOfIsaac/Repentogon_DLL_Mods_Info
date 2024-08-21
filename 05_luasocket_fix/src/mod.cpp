#include <lua.hpp>
#include "LuaCore.h"
#include "IsaacRepentance.h"
#include "HookSystem.h"

extern "C"
{
	#include "luasocket.h"
}

std::string version_str = "zhlLuaSocketFix by sublimnl - " + std::string(LUASOCKET_VERSION);

int luaopen_socket_core_override(lua_State* L) {
	luaopen_socket_core(L);

	lua_pushstring(L, "_VERSION");
	lua_pushstring(L, version_str.c_str());
	lua_settable(L, -3);

	return 1;
}

HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();

	lua_State* L = _state;
	lua::LuaStackProtector protector(L);

    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    lua_pushcfunction(L, luaopen_socket_core_override);
    lua_setfield(L, -2, "socket.core");
    lua_pop(L, 2);
/*
    luaopen_socket_core(L);
    lua_setglobal(L, "socket");
*/
}
