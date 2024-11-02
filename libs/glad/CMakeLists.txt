cmake_minimum_required(VERSION 3.8)
project(glad)

# Set compiler and flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors") 

if(LINUX)
  add_library(glad SHARED src/glad.c)
else()
  add_library(glad STATIC src/glad.c)
endif()

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

