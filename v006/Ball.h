#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
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

struct Ball {
  float y;
  float mass;
  float radius;
  float initial_velocity;
  float max_velocity;
  float velocity;
  Direction direction{Direction::NONE};
  int counter;

  static constexpr float MIN_MASS{20.0f};
  static constexpr float MAX_MASS{1200.0f};
  static constexpr float MIN_RADIUS{5.0f};
  static constexpr float MAX_RADIUS{100.0f};
};

void init_ball(Ball &b, float y, float mass, float max_velocity);
void change_mass(Ball &b, float mass);
void move_ball(Ball &b, float delta);
void render_ball(SDL_Renderer *renderer, SDL_Texture *ball_texture,
                 const Ball &b);

#endif // !BALL_H
