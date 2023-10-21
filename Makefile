CC = g++
COMPILER_FLAGS = -Wall -Wfatal-errors
SRC_FILES = src/*.cpp src/Game/*.cpp src/Logger/*.cpp src/ECS/*.cpp
LINKER_FLAGS = -lSDL2 -lSDL2_image -llua5.3
 
build : 
	$(CC) $(COMPILER_FLAGS) -std=c++17 -I"./libs/" $(SRC_FILES) $(LINKER_FLAGS) -o engine

run : build 
	./engine

clean :
	rm engine
