cmake_minimum_required(VERSION 3.5.1)
enable_language(CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# enable -fPIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)

project("mysql-ulid" VERSION 0.0.1 DESCRIPTION "MySQL UDF Plugin for generating ULIDs")

FILE(GLOB mysql_ulid_src "*.h" "*.cpp")

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

add_library(
    ulid SHARED
    ${mysql_ulid_src}
)
include_directories(ulid ${MYSQL_INCLUDE})
target_compile_options(ulid PUBLIC ${MYSQL_CXX_FLAGS})
