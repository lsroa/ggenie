cmake_minimum_required(VERSION 3.8)
project(ggenie)

# Set compiler and flags
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors") 

# Source files
file(GLOB_RECURSE SRC_FILES src/*.cpp) 

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

# Build executable
add_executable(engine ${SRC_FILES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
target_include_directories(engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(engine PRIVATE LDtkLoader glm SDL2_image::SDL2_image SDL2::SDL2)

# Run after build 
add_custom_command(TARGET engine
		POST_BUILD COMMAND ./engine
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Build for web
# set(EMCC_LINKER_FLAGS -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sNO_DISABLE_EXCEPTION_CATCHING)
# set(TARGET_NAME build/engine.html)
# add_custom_target(web
# 		COMMENT "Building for web ..."
# 		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
# 		SOURCES ${SRC_FILES}
# 		COMMAND ${CMAKE_COMMAND} -E make_directory build
# 		COMMAND emcc --preload-file ./assets ${SRC_FILES} -I "./libs/" ${EMCC_LINKER_FLAGS} -o ${TARGET_NAME} 
# 		COMMAND emrun --no_browser --port 8080 ${TARGET_NAME}
# )
# set_target_properties(web PROPERTIES COMPILE_DEFINITIONS "__EMSCRIPTEN__")
