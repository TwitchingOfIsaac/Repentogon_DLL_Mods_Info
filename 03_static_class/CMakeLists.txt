cmake_minimum_required(VERSION 3.13.0)

set (CMAKE_CXX_STANDARD 17)
set (MOD_NAME "Example MOD" CACHE PATH "The name of your mod")
set (REPENTOGON_SRC "../.." CACHE PATH "Path to the root of the Repentogon source directory")
set (ISAAC_DIRECTORY "" CACHE PATH "Path to the root directory of the gamei where isaac-ng.exe is")
set (CMAKE_BUILD_TYPE "Debug")

function(convert_to_pascal_case input output)
    string(REPLACE " " ";" words_list ${input})
    set(result "")

    foreach(word IN LISTS words_list)
        string(SUBSTRING ${word} 0 1 first_char)
        string(TOUPPER ${first_char} first_char)
        string(SUBSTRING ${word} 1 -1 rest)
        string(TOLOWER ${rest} rest)
        string(APPEND result "${first_char}${rest}")
    endforeach()

    set(${output} "zhl${result}" PARENT_SCOPE)
endfunction()

project(${MOD_NAME})

convert_to_pascal_case("${MOD_NAME}" zhlModName)

FILE(GLOB_RECURSE MOD_SRC ${CMAKE_SOURCE_DIR}/src/*.*)
foreach(_source IN ITEMS ${MOD_SRC})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
add_library(${zhlModName} SHARED ${MOD_SRC})

find_library(LUA_LIB NAMES Lua5.4 PATHS ${REPENTOGON_SRC}/build/release)
find_library(LIBZHL_LIB NAMES libzhl PATHS ${REPENTOGON_SRC}/build/release)

target_include_directories(${zhlModName} PUBLIC ${REPENTOGON_SRC}/include "${REPENTOGON_SRC}/libs/lua" 
    "${REPENTOGON_SRC}/libs/rapidxml" "${REPENTOGON_SRC}/libs/rapidjson/include/rapidjson" 
    "${REPENTOGON_SRC}/libs/LuaBridge/Source/LuaBridge" 
    "${REPENTOGON_SRC}/libzhl" "${REPENTOGON_SRC}/libs/imgui" 
    "${REPENTOGON_SRC}/libs/imgui/misc/freetype" "${REPENTOGON_SRC}/libs/imgui/backends" 
    "${REPENTOGON_SRC}/libs/NaturalSort" "${REPENTOGON_SRC}/libs/glad/include" "${REPENTOGON_SRC}/libs/mINI/src/mini"
    "${REPENTOGON_SRC}/libs/luasocket")
target_link_libraries(${zhlModName} ${LUA_LIB} ${LIBZHL_LIB})
target_compile_options(${zhlModName} PUBLIC "/MD")

if(NOT ISAAC_DIRECTORY STREQUAL "")
    message (STATUS "Files will be installed to " ${ISAAC_DIRECTORY})
    add_custom_command(TARGET ${zhlModName} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE_DIR:${zhlModName}>/${zhlModName}.dll" "${ISAAC_DIRECTORY}")
endif()

