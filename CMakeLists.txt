cmake_minimum_required(VERSION 3.8)
project(ggenie)

# Set compiler and flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors -Wno-macro-redefined") 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
file(GLOB_RECURSE SRC_FILES src/*.cpp) 
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics/pyrenderer.cpp)

# Build executable
add_executable(engine ${SRC_FILES})
add_library(gg_lib SHARED ${SRC_FILES})

if(APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif()

# Find SDL2 and SDL2_image libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Find LDtkLoader library
set(LDtkLoader_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/ldtk/lib/cmake/LDtkLoader)
find_package(LDtkLoader 1.4)

# Add glm library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

# Add glfw library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw-3.4)

# Add glad library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad)

# Add imgui library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)

# Add stb_image library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/stb_image)

# Add source includes 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (APPLE)
  find_library(OpenGL_LIBRARY OpenGL)
  # Suppress deprecation warnings of openGL for Apple 😒 
  add_definitions(-DGL_SILENCE_DEPRECATION)
else()
  find_package(OpenGL REQUIRED)
endif()

#Copy assets to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

#Copy python test scripts
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bindings/main.py DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bindings/gg.pyi DESTINATION ${CMAKE_BINARY_DIR})

if(APPLE)
  target_link_libraries(gg_lib PUBLIC LDtkLoader glm SDL2_image::SDL2_image SDL2::SDL2 glad imgui glfw ${OpenGL_LIBRARY})
endif()

target_link_libraries(engine PRIVATE gg_lib)

# Add Python bindings
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/pybind11/include)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
include_directories(${Python3_INCLUDE_DIRS})

set(PYBIND11_FINDPYTHON ON)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/pybind11)
include_directories(${PYBIND11_INCLUDE_DIR})
include_directories(${Python3_INCLUDE_DIRS})


pybind11_add_module(gg src/Graphics/pyrenderer.cpp)
target_link_libraries(gg PUBLIC gg_lib Python3::Python)
install(TARGETS gg DESTINATION .)

add_executable(grapper ${CMAKE_CURRENT_SOURCE_DIR}/bindings/engine.cpp)
target_link_libraries(grapper PUBLIC gg_lib Python3::Python)
target_include_directories(grapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(grapper PROPERTIES PREFIX "" SUFFIX ".so")
