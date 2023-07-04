cmake_minimum_required(VERSION 3.10)
enable_language(CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# enable -fPIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)

project("mysql-ulid" VERSION 0.0.1 DESCRIPTION "MySQL UDF Plugin for generating ULIDs")

# ----- mysql config
execute_process(
    COMMAND mysql_config --version
    OUTPUT_VARIABLE MYSQL_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE MYSQL_CONFIG_EXIT_STATUS
)
message("-- MySQL Library Version: ${MYSQL_VERSION}")
if (MYSQL_CONFIG_EXIT_STATUS)
    message(FATAL_ERROR "mysql_config command is not found. please install it and check version.")
endif()

execute_process(
    COMMAND mysql_config --cxxflags 
    OUTPUT_VARIABLE MYSQL_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE
)
message("-- MySQL CXX FLAGS: ${MYSQL_CXX_FLAGS}")
execute_process(
    COMMAND mysql_config --variable=pkgincludedir
    OUTPUT_VARIABLE MYSQL_INCLUDE OUTPUT_STRIP_TRAILING_WHITESPACE
)
message("-- MySQL INCLUDE Directory: ${MYSQL_INCLUDE}")
# --- mysql_config

# --- ulid build
FILE(GLOB mysql_ulid_src "src/*.cpp")
FILE(GLOB mysql_ulid_include "include/*.h")
add_library(
    ulid SHARED
    ${mysql_ulid_src}
)
include_directories(ulid ${MYSQL_INCLUDE} ${mysql_ulid_include})
target_compile_options(ulid PUBLIC ${MYSQL_CXX_FLAGS})
# --- ulid build

# --- gtest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/be03d00f5f0cc3a997d1a368bee8a1fe93651f48.zip
)
FetchContent_MakeAvailable(googletest)
FILE(GLOB mysql_ulid_test "test/*.cpp")

add_executable(ulid-gtest ${mysql_ulid_src} ${mysql_ulid_test})
target_link_libraries(ulid-gtest gtest_main)
target_include_directories(ulid-gtest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME test COMMAND ulid-gtest)
enable_testing()
# --- gtest