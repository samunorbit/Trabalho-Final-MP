OBJS = main.cpp game.cpp unidades.cpp

OBJ_NAME = game

CC = g++

INCLUDE_PATHS = -I.\SDL2_MinGW_32Bit\include

LIBRARY_PATHS = -L.\SDL2_MinGW_32Bit\lib

FLAGS = -std=c++11 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all : $(OBJS)
	g++ $(OBJS)  $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(FLAGS) -o $(OBJ_NAME)
