cmake_minimum_required(VERSION 3.27)
project(terminal_inventory_system)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLiteCpp CONFIG REQUIRED)

add_executable(terminal_inventory_system main.cpp)

target_link_libraries(terminal_inventory_system PRIVATE SQLiteCpp)
