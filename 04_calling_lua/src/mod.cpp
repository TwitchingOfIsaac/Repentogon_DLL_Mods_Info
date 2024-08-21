#include <lua.hpp>
#include "LuaCore.h"
#include "IsaacRepentance.h"
#include "HookSystem.h"
#include <iostream>
#include <string>
#include <variant>
#include <vector>

// Using std::variant for dynamic argument types
using LuaArg = std::variant<const char *, int, double, bool, lua_CFunction, void *>;

void CallLua(const char *table, const char *function, const std::vector<LuaArg> &args)
{
    lua_State *L = g_LuaEngine->_state;

    // Get the global table
    lua_getglobal(L, table);

    // Get the function from the table
    lua_getfield(L, -1, function);

    // Check if it is a function
    if (lua_isfunction(L, -1))
    {
        // Push the arguments dynamically
        for (const auto &arg : args)
        {
            if (std::holds_alternative<const char *>(arg))
            {
                lua_pushstring(L, std::get<const char *>(arg));
            }
            else if (std::holds_alternative<int>(arg))
            {
                lua_pushinteger(L, std::get<int>(arg));
            }
            else if (std::holds_alternative<double>(arg))
            {
                lua_pushnumber(L, std::get<double>(arg));
            }
            else if (std::holds_alternative<bool>(arg))
            {
                lua_pushboolean(L, std::get<bool>(arg));
            }
            else if (std::holds_alternative<lua_CFunction>(arg))
            {
                lua_pushcfunction(L, std::get<lua_CFunction>(arg));
            }
            else if (std::holds_alternative<void *>(arg))
            {
                lua_pushlightuserdata(L, std::get<void *>(arg));
            }
            else
            {
                std::cerr << "Unhandled argument type!" << std::endl;
            }
        }

        // Call the function with the correct number of arguments
        int numArgs = args.size();
        if (lua_pcall(L, numArgs, 0, 0) != LUA_OK)
        {
            const char *error = lua_tostring(L, -1);
            std::cerr << "Error calling Lua function: " << error << std::endl;
            lua_pop(L, 1); // Pop the error message from the stack
        }
    }
    else
    {
        std::cerr << function << " is not a valid function in table " << table << std::endl;
        lua_pop(L, 1); // Pop non-function value
    }

    // Pop the table off the stack
    lua_pop(L, 1);
}

HOOK_METHOD(Entity_Player, AddCoins, (int amount)->void)
{
    super(amount);

    std::string notificationMessage;
    switch (amount)
    {
    case 1:
        notificationMessage = "You picked up a penny!";
        break;
    case 5:
        notificationMessage = "You picked up a nickel!";
        break;
    case 10:
        notificationMessage = "You picked up a dime!";
        break;
    case 25:
        notificationMessage = "You picked up a quarter!";
        break;
    default:
        notificationMessage = "You picked up " + std::to_string(amount) + " coins!";
        break;
    }

    if (amount > 0)
    {
        // Call the Lua function to push a notification
        // ImGui.PushNotification(notificationMessage, 0, 5000)
        // https://repentogon.com/ImGui.html?h=#pushnotification
        CallLua("ImGui", "PushNotification", std::vector<LuaArg>{notificationMessage.c_str(), 0, 5000});
    }
}