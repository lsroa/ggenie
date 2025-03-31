cmake_minimum_required(VERSION 3.10)
project(imgui)

# Set compiler and flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors") 

file(GLOB SRC_FILES "*.cpp")

add_library(imgui SHARED ${SRC_FILES})
target_include_directories(imgui PUBLIC SRC_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../glfw-3.4/include)
target_link_libraries(imgui PUBLIC glfw)
