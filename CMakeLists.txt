cmake_minimum_required(VERSION 3.8)
project(ggenie)

# Set compiler and flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors -Wno-macro-redefined") 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
file(GLOB_RECURSE SRC_FILES src/*.cpp) 

# Build executable
add_executable(engine ${SRC_FILES})

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
target_include_directories(engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/stb_image)

if (APPLE)
  find_library(OpenGL_LIBRARY OpenGL)
  # Suppress deprecation warnings of openGL for Apple 😒 
  add_definitions(-DGL_SILENCE_DEPRECATION)
else()
  find_package(OpenGL REQUIRED)
endif()

#Copy assets to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(APPLE)
  target_link_libraries(engine PRIVATE LDtkLoader glm SDL2_image::SDL2_image SDL2::SDL2 glad imgui glfw ${OpenGL_LIBRARY})
else()
  target_link_libraries(painter PRIVATE LDtkLoader glm SDL2_image::SDL2_image SDL2::SDL2 glad imgui glfw OpenGL::GL)
endif()
