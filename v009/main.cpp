#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>

struct Window {
  float width;
  float height;
};

struct Paddle {
  float width;
  float height;
};

struct Ball {
  float radius;
  float velocity;
};

bool starts_with(const char *str, const char *search);
bool ends_with(const char *str, const char *search);
size_t get_file_length(FILE *file);
void clear_string(char *str);
void extract_option(char *dest, const char *str, size_t start);

int main(int argc, char *argv[]) {
  const char *filename = "ball.config";

  FILE *config = fopen(filename, "r");
  if (!config) {
    printf("Failed to open file %s\n", filename);
    return 1;
  }

  size_t size = get_file_length(config);
  char line[size];
  char section[size];
  char option[size];

  Window *wnd = NULL;
  Paddle *paddle = NULL;
  Ball *ball = NULL;

  while (fgets(line, size, config)) {
    if (starts_with(line, "[")) {
      char *bracket = strchr(line, ']');
      if (bracket) {
        size_t index = bracket - line;
        clear_string(section);
        strncpy(section, &line[1], index - 1);
      }
    } else {
      if (strncmp(section, "Window", 6) == 0) {
        if (!wnd) {
          wnd = (Window *)malloc(sizeof(Window));
        }

        if (starts_with(line, "width=")) {
          extract_option(option, line, 6);
          wnd->width = atof(option);
        } else if (starts_with(line, "height=")) {
          extract_option(option, line, 7);
          wnd->height = atof(option);
        }
      } else if (strncmp(section, "Paddle", 6) == 0) {
        if (!paddle) {
          paddle = (Paddle *)malloc(sizeof(Paddle));
        }

        if (starts_with(line, "width=")) {
          extract_option(option, line, 6);
          paddle->width = atof(option);
        } else if (starts_with(line, "height=")) {
          extract_option(option, line, 7);
          paddle->height = atof(option);
        }
      } else if (strncmp(section, "Ball", 4) == 0) {
        if (!ball) {
          ball = (Ball *)malloc(sizeof(Ball));
        }

        if (starts_with(line, "radius=")) {
          extract_option(option, line, 7);
          ball->radius = atof(option);
        } else if (starts_with(line, "velocity=")) {
          extract_option(option, line, 9);
          ball->velocity = atof(option);
        }
      }
    }
  }

  if (wnd) {
    free(wnd);
  }

  if (paddle) {
    free(paddle);
  }

  if (ball) {
    free(ball);
  }

  fclose(config);

  return 0;
}

bool starts_with(const char *str, const char *search) {
  size_t length = strlen(search);

  for (size_t i = 0; i < length; ++i) {
    if (str[i] != search[i]) {
      return false;
    }
  }

  return true;
}

bool ends_with(const char *str, const char *search) {
  size_t str_length = strlen(str);
  size_t search_length = strlen(search);

  for (size_t i = 0; i < search_length; ++i) {
    if (search[i] != str[str_length - search_length + i]) {
      return false;
    }
  }

  return true;
}

size_t get_file_length(FILE *file) {
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  return size;
}

void clear_string(char *str) {
  size_t size = strlen(str);
  if (size > 0) {
    memset(str, '\0', size);
  }
}

void extract_option(char *dest, const char *str, size_t start) {
  clear_string(dest);

  size_t index = start;
  while (isalnum(str[index])) {
    ++index;
  }

  strncpy(dest, &str[start], index - start);
}
