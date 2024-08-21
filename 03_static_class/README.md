## 3. Static Class
In this mod, we will be creating a static `Strings` class with various methods for string manipulation. We will introduce returning values from `LUA_FUNCTION`s.

## Code Overview
The code is available in the `mod.cpp` file and won't be reproduced here to save space. For an introduction to `LUA_FUNCTION` and `HOOK_METHOD`, refer to previous mod examples.

### `LUA_FUNCTION` Return Values
In the following examples, we will return values from the functions.

#### Returning a String
Most of the functions defined in the mod code return strings:
```cpp
LUA_FUNCTION(Lua_String_ToUpper) {
    std::string str = luaL_checkstring(L, 1);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    lua_pushstring(L, str.c_str());
    return 1;
}
```
After defining the LUA_FUNCTION, we grab the first parameter passed into the function and validate that it is a string using luaL_checkstring. If the argument is not a string, an error will be thrown (e.g., "bad argument #1 to 'ToUpper' (string expected, got table)"). Next, we perform the transformation on the str variable to make it all uppercase. After that, we push the string onto the stack and return 1, indicating that we have added one item to the stack.

In Lua, we can call this function as follows:
```lua
local upperCasedString = Strings.ToUpper('my original string');
```
This will pop the value returned from the stack into the local variable.

#### Returning an integer
This is similar to returning a string, but uses lua_pushinteger instead of lua_pushstring:
```cpp
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
```

#### Return a table
This example demonstrates taking two values and returning a table:
```cpp
LUA_FUNCTION(Lua_String_Split) {
    std::string str = luaL_checkstring(L, 1);
    std::string delimiter = luaL_checkstring(L, 2);

    lua_newtable(L);
    size_t pos = 0;
    int index = 1;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        std::string token = str.substr(0, pos);
        lua_pushstring(L, token.c_str());
        lua_rawseti(L, -2, index++);
        str.erase(0, pos + delimiter.length());
    }

    lua_pushstring(L, str.c_str());
    lua_rawseti(L, -2, index);

    return 1;
}
```
The function signature for this method is Split(str, delimiter). On line 2, we validate the first parameter with luaL_checkstring; on line 3, we do the same for the second parameter. These values are popped from the stack and assigned to local variables.

We then create a new table (note that tables in Lua are 1-indexed) and initialize it on line 7.

The while loop splits the string by the delimiter and pushes the resulting substrings onto the stack. We use lua_rawseti to insert the stack contents into the table at the correct index.

Finally, the remaining string is pushed onto the stack and inserted into the table, leaving the table as the last element on the stack, which is then returned.

## Building
Follow the standard build process from the root of this repository.
![03_static_class_cmake](/_images/03_static_class_cmake.png)

## Testing
Once you have added the newly generated DLL to the Isaac Directory (or had CMake do that for you automatically), start Isaac. In the Debug Console, you can test out some of the methods:
```
lua print(Strings.ToUpper('all lowercase'))
lua print(Strings.ToSnakeCase('this is an example'))
lua print(Strings.ToKebabCase('this is an example'))
lua print(Strings.ToPascalCase('this is an example'))
lua print(Strings.ToTitleCase('this is an example'))
lua print(Strings.ToLeetSpeak('this is an example'))
lua local words = Strings.Split('all the words', ' '); for i = 1, #words do print(Strings.Reverse(words[i])); end
lua print(Strings.Shuffle('abcdefghijklmnopqrstuvwxyz'))
```
If the mod was loaded successfully, you should see the following in your console:
![03_static_class](/_images/03_static_class.png)

