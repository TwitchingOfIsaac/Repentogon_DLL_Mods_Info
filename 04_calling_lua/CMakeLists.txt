cmake_minimum_required(VERSION 3.13.0)

include(../cmake_helpers/functions.cmake)

set(MOD_NAME "Example MOD" CACHE PATH "The name of your mod")
set(ISAAC_DIRECTORY "" CACHE PATH "Path to the root directory of the gamei where isaac-ng.exe is")
set(REPENTOGON_SRC "D:/Development/REPENTOGON" CACHE PATH "Path to the root of the Repentogon source directory")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 17)

project(${MOD_NAME})
convert_to_pascal_case("${MOD_NAME}" zhlModName)

message(STATUS "Mod name: ${MOD_NAME}")
message(STATUS "Mod will be built as: ${zhlModName}.dll")

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

target_include_directories(${zhlModName} PUBLIC
    ${REPENTOGON_SRC}/include
    ${REPENTOGON_SRC}/libs/lua
    ${REPENTOGON_SRC}/libzhl
    ${REPENTOGON_SRC}/libs/rapidxml
)

target_link_libraries(${zhlModName} ${LUA_LIB} ${LIBZHL_LIB})
target_compile_options(${zhlModName} PUBLIC "/MD")

if(NOT ISAAC_DIRECTORY STREQUAL "")
    message (STATUS "Files will be installed to " ${ISAAC_DIRECTORY})
    add_custom_command(TARGET ${zhlModName} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE_DIR:${zhlModName}>/${zhlModName}.dll" "${ISAAC_DIRECTORY}")
endif()
