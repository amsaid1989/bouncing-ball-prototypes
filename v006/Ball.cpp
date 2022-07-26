#include "Ball.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdio.h>

void calculate_ball_values_from_mass(Ball &b, float mass, float window_width) {
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

  b.x = (window_width / 2) - b.radius;

  b.velocity = b.initial_velocity = (1 / pow(b.mass, 0.35)) * 30000;
  if (b.velocity > b.max_velocity) {
    b.velocity = b.initial_velocity = b.max_velocity;
  }
}

void init_ball(Ball &b, float y, float mass, float max_velocity,
               float window_width) {
  b.y = y;
  b.max_velocity = max_velocity;

  calculate_ball_values_from_mass(b, mass, window_width);

  b.prev_x = -1;
  b.prev_y = -1;
}

void change_mass(Ball &b, float mass, float window_width) {
  calculate_ball_values_from_mass(b, mass, window_width);
}

float calculate_new_position(Ball &b, float delta) {
  float acceleration = GRAVITY * b.mass;

  b.velocity += acceleration * delta;
  if (b.velocity > b.max_velocity) {
    b.velocity = b.max_velocity;
  }

  return b.y + (b.velocity * delta) + (0.5 * acceleration * delta * delta);
}

bool goes_through_paddle(const Ball &b, const Paddle &p, float delta) {
  // Exit if ball is moving up
  if (b.prev_y > b.y) {
    return false;
  }

  float ball_prev_centre_x = b.prev_x + b.radius;
  float ball_current_centre_x = b.x + b.radius;

  float paddle_prev_left = p.prev_x;
  float paddle_prev_right = p.prev_x + p.width;

  // Copy the ball and calculate its next position. We need to calculate the
  // next position to prevent the ball from visually going through the paddle.
  // Otherwise, the ball will go through, and then the game would fix that by
  // bringing it back. By calculating the next position of the ball, we prevent
  // the ball from visually going through the paddle at all.
  Ball copy = b;
  copy.y = calculate_new_position(copy, delta);

  // If the ball movement vector intersects the paddle's top, both dx and dy
  // should be negative
  float dx = (paddle_prev_left - ball_prev_centre_x) *
             (paddle_prev_right - ball_current_centre_x);
  float dy =
      (p.y - (b.y + (b.radius * 2))) * (p.y - (copy.y + (copy.radius * 2)));

  if (!(dx < 0) || !(dy < 0)) {
    return false;
  }

  return true;
}

bool collides_with_paddle(const Ball &b, const Paddle &p) {
  float ball_left = b.x;
  float ball_right = b.x + b.radius * 2.0f;
  float ball_top = b.y;
  float ball_bottom = b.y + b.radius * 2.0f;

  float paddle_left = p.x;
  float paddle_right = p.x + p.width;
  float paddle_top = p.y;
  float paddle_bottom = p.y + p.height;

  if (ball_left > paddle_right || ball_right < paddle_left ||
      ball_top > paddle_bottom || ball_bottom < paddle_top) {
    return false;
  }

  return true;
}

void move_ball(Ball &b, const Paddle &p, float window_width,
               float window_height, int &score, float delta) {
  /*
   * Instead of passing the score directly, an event system would be a good
   * idea where the ball emits an event every time it collides with the paddle
   * so the Game object can increment the score.
   */

  if (score > 0 && score % 5 == 0) {
    change_mass(b, b.mass - 100.0f, window_width);
  }

  float newY = calculate_new_position(b, delta);

  if (newY < 0) {
    newY = 0;
    b.direction = Direction::POS;
    b.velocity = get_direction_value(b.direction) * b.initial_velocity;
  } else if (goes_through_paddle(b, p, delta) || collides_with_paddle(b, p)) {
    newY = p.y - b.radius * 2.0f - 1.0f;
    b.direction = Direction::NEG;
    b.velocity = get_direction_value(b.direction) * b.initial_velocity;

    ++score;
  }

  b.prev_x = b.x;
  b.prev_y = b.y;

  b.y = newY;
}

void render_ball(const Ball &b, float window_width, float window_height,
                 SDL_Renderer *renderer, SDL_Texture *ball_texture) {
  SDL_FRect dest{b.x, b.y, b.radius * 2.0f, b.radius * 2.0f};
  SDL_RenderCopyF(renderer, ball_texture, NULL, &dest);
}
