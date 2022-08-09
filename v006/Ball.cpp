#include "Ball.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <math.h>

void calculate_ball_values_from_mass(Ball &b, float mass) {
  if (mass < Ball::MIN_MASS) {
    mass = Ball::MIN_MASS;
  } else if (mass > Ball::MAX_MASS) {
    mass = Ball::MAX_MASS;
  }

  b.mass = mass;
  b.radius = pow(b.mass, 0.65);

  if (b.radius < Ball::MIN_RADIUS) {
    b.radius = Ball::MIN_RADIUS;
  } else if (b.radius > Ball::MAX_RADIUS) {
    b.radius = Ball::MAX_RADIUS;
  }

  b.velocity = b.initial_velocity = (1 / pow(b.mass, 0.35)) * 30000;
  if (b.velocity > b.max_velocity) {
    b.velocity = b.initial_velocity = b.max_velocity;
  }
}

void init_ball(Ball &b, float y, float mass, float max_velocity) {
  b.y = y;
  b.max_velocity = max_velocity;

  calculate_ball_values_from_mass(b, mass);
}

void change_mass(Ball &b, float mass) {
  calculate_ball_values_from_mass(b, mass);
}

void move_ball(Ball &b, float delta) {
  if (b.counter > 0 && b.counter % 5 == 0) {
    change_mass(b, b.mass - 100.0f);
  }

  float acceleration = GRAVITY * b.mass;

  b.velocity += acceleration * delta;
  if (b.velocity > b.max_velocity) {
    b.velocity = b.max_velocity;
  }

  float newY =
      b.y + (b.velocity * delta) + (0.5 * acceleration * delta * delta);

  if (newY < 0) {
    newY = 0;
    b.direction = Direction::POS;
    b.velocity = get_direction_value(b.direction) * b.initial_velocity;
  } else if (newY > SCREEN_HEIGHT - b.radius * 2.0f) {
    newY = SCREEN_HEIGHT - b.radius * 2.0f;
    b.direction = Direction::NEG;
    b.velocity = get_direction_value(b.direction) * b.initial_velocity;

    ++(b.counter);
  }

  b.y = newY;
}

void render_ball(SDL_Renderer *renderer, SDL_Texture *ball_texture,
                 const Ball &b) {
  SDL_FRect dest{(SCREEN_WIDTH / 2.0f) - b.radius, b.y, b.radius * 2.0f,
                 b.radius * 2.0f};
  SDL_RenderCopyF(renderer, ball_texture, NULL, &dest);
}
