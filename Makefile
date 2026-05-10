# Declare variables
CC = g++
LANG_STD = -std=c++23
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = src/*.cpp \
			src/Game/*.cpp \
			src/Logger/*.cpp
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3
SDL_FLAGS = `pkg-config --cflags --libs sdl2`
OBJECT_NAME = gameengine

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(SDL_FLAGS) $(LINKER_FLAGS) -o $(OBJECT_NAME);

run:
	./$(OBJECT_NAME)

clean:
	rm $(OBJECT_NAME)

all: clean build run