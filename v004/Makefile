CC=clang++
COMPILER_FLAGS=-g -std=c++20 -Wall -Wpedantic $(shell pkg-config --cflags sdl2)
LINKER_FLAGS=$(shell pkg-config --libs SDL2_image)
OBJS=*.cpp

all: $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(OBJS) -o main
