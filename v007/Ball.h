#ifndef BALL_H
#define BALL_H

#include "Paddle.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <math.h>

enum class Direction {
  NEG,
  NONE,
  POS,

  TOTAL
};
inline int get_direction_value(Direction dir) {
  return (int)floor((float)dir - 0.5);
}
inline Direction float_to_direction(float f) {
  bool valid = f < (float)Direction::TOTAL;

  if (!valid) {
    printf("%f is not a valid direction. It should be between %d and %d.\n", f,
           (int)Direction::NEG, (int)Direction::POS);
  }

  assert(valid);

  return (Direction)round(f);
}

struct Ball {
  float x;
  float y;
  float prev_x;
  float prev_y;
  float mass;
  float radius;
  float initial_velocity;
  float max_velocity;
  float xvel;
  float yvel;
  Direction xdir{Direction::NONE};
  Direction ydir{Direction::NONE};
  int counter;

  NON_INSTANCE_MEMBER const float NORMALISER;
  NON_INSTANCE_MEMBER constexpr float MIN_MASS{20.0f};
  NON_INSTANCE_MEMBER constexpr float MAX_MASS{1200.0f};
  NON_INSTANCE_MEMBER constexpr float MIN_RADIUS{10.0f};
  NON_INSTANCE_MEMBER constexpr float MAX_RADIUS{100.0f};
};

void init_ball(Ball &b, float y, float mass, float max_velocity,
               float window_width);
void move_ball(Ball &b, const Paddle &p, float window_width,
               float window_height, int &score, float delta);
void render_ball(const Ball &b, float window_width, float window_height,
                 SDL_Renderer *renderer, SDL_Texture *ball_texture);

#endif // !BALL_H
