#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

enum Direction { DOWN = 1, UP = -1 };

struct Point {
  float x;
  float y;
};

struct Ball {
  float radius;
  float mass;
  float v0;
  float v;
  Uint32 t0;
  Uint32 t;
  float h0;
  float rho;
  Point position;
  Direction direction;
};

void move_ball(Ball &b);
void render_ball(SDL_Renderer *renderer, const Ball &b);

#endif // !BALL_H
