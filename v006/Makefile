CC=clang++
CFLAGS=-std=c++20 -g $(shell pkg-config --cflags sdl2 SDL2_image)
LIBS=$(shell pkg-config --libs sdl2 SDL2_image)
SRC=*.cpp

all:
	$(CC) $(CFLAGS) $(LIBS) $(SRC) -o main
