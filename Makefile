CC = g++

ifeq ($(shell uname), Darwin)
	COMPILER_FLAGS = -Wall -Wfatal-errors -std=c++17 \
	-I/opt/homebrew/include \
	-L/opt/homebrew/lib
	LUA_LINKER_FLAGS = -llua
else
	COMPILER_FLAGS = -Wall -Wfatal-errors -std=c++17 
	LUA_LINKER_FLAGS = -llua5.3
endif

SRC_FILES = src/*.cpp src/Game/*.cpp src/Logger/*.cpp src/ECS/*.cpp
LINKER_FLAGS = -lSDL2 -lSDL2_image $(LUA_LINKER_FLAGS)
 
build : 
	$(CC) $(COMPILER_FLAGS) -I"./libs/" $(SRC_FILES) $(LINKER_FLAGS) -o engine

run : build 
	./engine

clean :
	rm engine
