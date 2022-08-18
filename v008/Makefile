CC=clang++
CFLAGS=-std=c++20 -g $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
LIBS=$(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)
SRC=*.cpp

all:
	$(CC) $(CFLAGS) $(LIBS) $(SRC) -o main
