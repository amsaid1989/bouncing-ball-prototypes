#include "Ball.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <cstdio>
#include <cstdlib>
#include <math.h>

float dt{};

void move_ball(Ball &b) {
  b.t = SDL_GetTicks();
  dt = (b.t - b.t0) / 1000.0f;

  float dv = b.v0 + (GRAVITY * dt);

  if (b.v < 0 && dv > 0) {
    b.h0 = b.position.y;
    b.v0 = b.v = 0.0f;
    b.t0 = b.t;
  } else {
    b.v = dv;

    float new_height = b.h0 + (b.v0 * dt) + (0.5f * GRAVITY * dt * dt);

    if (new_height > SCREEN_HEIGHT - b.radius) {
      b.h0 = new_height = SCREEN_HEIGHT - b.radius;
      b.v0 = b.v = -1 * b.v * b.rho;
      b.t0 = b.t;
    }

    b.position.y = new_height;
  }
}

void render_ball(SDL_Renderer *renderer, const Ball &b) {
  SDL_FRect dest{b.position.x, b.position.y, b.radius, b.radius};

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRectF(renderer, &dest);
}
