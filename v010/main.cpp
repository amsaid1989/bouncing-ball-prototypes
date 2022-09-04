#include "FileReader.h"
#include "string_utils.h"
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

int main(int argc, char *argv[]) {

  Window *wnd = NULL;
  Paddle *paddle = NULL;
  Ball *ball = NULL;

  FileReader reader;
  if (!init_config_loader(&reader, "ball.config")) {
    printf("Failed to initialise configuration\n");
    return 1;
  }

  char section[reader.size];
  char option[reader.size];

  for (size_t i = 0; i < reader.line_count; ++i) {
    const char *line = reader.lines[i];

    if (starts_with(line, "[")) {
      const char *bracket = strchr(line, ']');
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
    printf("Window width: %f\n", wnd->width);
    printf("Window height: %f\n", wnd->height);
    free(wnd);
  }

  if (paddle) {
    printf("Paddle width: %f\n", paddle->width);
    printf("Paddle height: %f\n", paddle->height);
    free(paddle);
  }

  if (ball) {
    printf("Ball radius: %f\n", ball->radius);
    printf("Ball velocity: %f\n", ball->velocity);
    free(ball);
  }

  destroy_config_loader(&reader);

  return 0;
}
