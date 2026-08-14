cmake_minimum_required(VERSION 3.16)
project(CowboyQuickdraw VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(cowboy_quickdraw
    src/driver.cpp
    src/utils.cpp
    db/sqlite3.c
)

target_include_directories(cowboy_quickdraw PRIVATE includes db)

find_package(Threads REQUIRED)
target_link_libraries(cowboy_quickdraw PRIVATE Threads::Threads ${CMAKE_DL_LIBS})