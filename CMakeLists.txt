cmake_minimum_required(VERSION 3.5.1)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("mysql-ulid" VERSION 0.0.1 DESCRIPTION "MySQL UDF Plugin for generating ULIDs")

FILE(GLOB mysql_ulid_src "*.h" "*.cpp")

add_compile_options(-I/usr/local/Cellar/mysql/8.0.33_3/include/mysql -fPIC)

add_library(
    ulid SHARED
    ${mysql_ulid_src}
)

