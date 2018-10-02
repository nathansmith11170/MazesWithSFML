OBJS = Maze.cpp

CC = g++

COMPILER_FLAGS = -w -g -pedantic -std=c++17

LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ_NAME = maze

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 