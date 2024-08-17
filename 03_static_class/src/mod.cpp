#include <fstream>
#include <lua.hpp>
#include <string>
#include <algorithm>
#include <cctype>
#include <random>
#include <sstream>
#include "LuaCore.h"
#include "IsaacRepentance.h"
#include "HookSystem.h"
#include "mod.h"

using namespace std;

extern "C" __declspec(dllexport) int ModInit(int argc, char** argv) {
    return 0;
}

// ToUpper function
LUA_FUNCTION(Lua_String_ToUpper) {
    std::string str = luaL_checkstring(L, 1);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    lua_pushstring(L, str.c_str());
    return 1;
}

// ToLower function
LUA_FUNCTION(Lua_String_ToLower) {
    std::string str = luaL_checkstring(L, 1);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    lua_pushstring(L, str.c_str());
    return 1;
}

// ToSnakeCase function
LUA_FUNCTION(Lua_String_ToSnakeCase) {
    std::string str = luaL_checkstring(L, 1);
    std::string result;

    for (char& c : str) {
        if (c == ' ') {
            result += '_';
        } else {
            result += std::tolower(c);
        }
    }

    lua_pushstring(L, result.c_str());
    return 1;
}

// Capitalize function
LUA_FUNCTION(Lua_String_Capitalize) {
    std::string str = luaL_checkstring(L, 1);
    bool capitalizeNext = true;

    for (char& c : str) {
        if (std::isspace(c)) {
            capitalizeNext = true;
        } else if (capitalizeNext) {
            c = std::toupper(c);
            capitalizeNext = false;
        }
    }

    lua_pushstring(L, str.c_str());
    return 1;
}

// PascalCase function
LUA_FUNCTION(Lua_String_ToPascalCase) {
    std::string str = luaL_checkstring(L, 1);
    std::string result;
    bool capitalizeNext = true;

    for (char& c : str) {
        if (std::isspace(c)) {
            capitalizeNext = true;
        } else {
            result += capitalizeNext ? std::toupper(c) : std::tolower(c);
            capitalizeNext = false;
        }
    }

    lua_pushstring(L, result.c_str());
    return 1;
}

// KebabCase function
LUA_FUNCTION(Lua_String_ToKebabCase) {
    std::string str = luaL_checkstring(L, 1);
    std::string result;

    for (char& c : str) {
        if (c == ' ') {
            result += '-';
        } else {
            result += std::tolower(c);
        }
    }

    lua_pushstring(L, result.c_str());
    return 1;
}

// Reverse function
LUA_FUNCTION(Lua_String_Reverse) {
    std::string str = luaL_checkstring(L, 1);
    std::reverse(str.begin(), str.end());
    lua_pushstring(L, str.c_str());
    return 1;
}

// CamelCase function
LUA_FUNCTION(Lua_String_ToCamelCase) {
    std::string str = luaL_checkstring(L, 1);
    std::string result;
    bool capitalizeNext = false;

    for (char& c : str) {
        if (std::isspace(c)) {
            capitalizeNext = true;
        } else {
            result += capitalizeNext ? std::toupper(c) : std::tolower(c);
            capitalizeNext = false;
        }
    }

    if (!result.empty()) {
        result[0] = std::tolower(result[0]);
    }

    lua_pushstring(L, result.c_str());
    return 1;
}

// TitleCase function
LUA_FUNCTION(Lua_String_ToTitleCase) {
    std::string str = luaL_checkstring(L, 1);
    bool capitalizeNext = true;

    for (char& c : str) {
        if (std::isspace(c)) {
            capitalizeNext = true;
        } else if (capitalizeNext) {
            c = std::toupper(c);
            capitalizeNext = false;
        } else {
            c = std::tolower(c);
        }
    }

    lua_pushstring(L, str.c_str());
    return 1;
}

// LeetSpeak function
LUA_FUNCTION(Lua_String_ToLeetSpeak) {
    std::string str = luaL_checkstring(L, 1);

    for (char& c : str) {
        switch (std::tolower(c)) {
            case 'a': c = '4'; break;
            case 'e': c = '3'; break;
            case 'i': c = '1'; break;
            case 'o': c = '0'; break;
            case 's': c = '5'; break;
            case 't': c = '7'; break;
        }
    }

    lua_pushstring(L, str.c_str());
    return 1;
}

// Shuffle function
LUA_FUNCTION(Lua_String_Shuffle) {
    std::string str = luaL_checkstring(L, 1);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(str.begin(), str.end(), g);
    lua_pushstring(L, str.c_str());
    return 1;
}

// IsPalindrome function
LUA_FUNCTION(Lua_String_IsPalindrome) {
    std::string str = luaL_checkstring(L, 1);
    std::string original = str;
    std::reverse(str.begin(), str.end());
    lua_pushboolean(L, original == str);
    return 1;
}

// WordCount function
LUA_FUNCTION(Lua_String_WordCount) {
    std::string str = luaL_checkstring(L, 1);
    std::istringstream stream(str);
    std::string word;
    int count = 0;

    while (stream >> word) {
        count++;
    }

    lua_pushinteger(L, count);
    return 1;
}

// Truncate function
LUA_FUNCTION(Lua_String_Truncate) {
    std::string str = luaL_checkstring(L, 1);
    int length = luaL_checkinteger(L, 2);

    if (str.length() > length) {
        str = str.substr(0, length);
    }

    lua_pushstring(L, str.c_str());
    return 1;
}

// RegisterClasses hook
HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
    super();

    lua_State* L = _state;
    lua::LuaStackProtector protector(L);

    lua_newtable(L);

    lua::TableAssoc(L, "ToUpper", Lua_String_ToUpper);
    lua::TableAssoc(L, "ToLower", Lua_String_ToLower);
    lua::TableAssoc(L, "ToSnakeCase", Lua_String_ToSnakeCase);
    lua::TableAssoc(L, "Capitalize", Lua_String_Capitalize);
    lua::TableAssoc(L, "ToPascalCase", Lua_String_ToPascalCase);
    lua::TableAssoc(L, "ToKebabCase", Lua_String_ToKebabCase);
    lua::TableAssoc(L, "Reverse", Lua_String_Reverse);
    lua::TableAssoc(L, "ToCamelCase", Lua_String_ToCamelCase);
    lua::TableAssoc(L, "ToTitleCase", Lua_String_ToTitleCase);
    lua::TableAssoc(L, "ToLeetSpeak", Lua_String_ToLeetSpeak);
    lua::TableAssoc(L, "Shuffle", Lua_String_Shuffle);
    lua::TableAssoc(L, "IsPalindrome", Lua_String_IsPalindrome);
    lua::TableAssoc(L, "WordCount", Lua_String_WordCount);
    lua::TableAssoc(L, "Truncate", Lua_String_Truncate);

    lua_setglobal(L, "Strings");
}

