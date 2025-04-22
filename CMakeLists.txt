cmake_minimum_required(VERSION 3.10)
project(ggenie)

# Set compiler and flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors -Wno-macro-redefined") 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Bindings/main.py DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Bindings/gg.pyi DESTINATION ${CMAKE_BINARY_DIR})


# Source files
file(GLOB_RECURSE SRC_FILES src/*.cpp) 
add_library(gg_core SHARED ${SRC_FILES})

if(APPLE)
  target_link_libraries(gg_core PUBLIC LDtkLoader glm SDL2_image::SDL2_image SDL2::SDL2 glad imgui glfw ${OpenGL_LIBRARY})
endif()

# Add Python bindings
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/pybind11/include)
find_package(Python3 3.11 REQUIRED COMPONENTS Interpreter Development)
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})
set(PYTHON_INCLUDE_DIRS ${Python3_INCLUDE_DIRS})
set(PYTHON_LIBRARIES ${Python3_LIBRARIES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/pybind11)
include_directories(${PYBIND11_INCLUDE_DIR})
include_directories(${Python3_INCLUDE_DIRS})

FILE(GLOB BINDINGS_SRC bindings/*.cpp)
pybind11_add_module(gg ${BINDINGS_SRC})
target_link_libraries(gg PUBLIC gg_core ${Python3_LIBRARIES})
install(TARGETS gg DESTINATION .)

add_executable(engine bin/main.cpp)
target_include_directories(engine PUBLIC bindings)
target_link_libraries(engine PUBLIC gg_core pybind11::embed ${Python3_LIBRARIES})


add_custom_target(
  copy_assets
  ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/assets 
  ${CMAKE_BINARY_DIR}/assets
)
