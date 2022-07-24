#include "Game.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <math.h>

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;
};

Game *init_game() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialise SDL\n");
    return NULL;
  }

  SDL_Window *window = SDL_CreateWindow("Bouncy Ball", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Failed to create window! SDL Error: %s\n", SDL_GetError());
    return NULL;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    printf("Failed to create renderer! SDL Error: %s\n", SDL_GetError());
    return NULL;
  }

  return new Game{window, renderer, true};
}

void close_game(Game *g) {
  SDL_DestroyRenderer(g->renderer);
  g->renderer = NULL;

  SDL_DestroyWindow(g->window);
  g->window = NULL;

  SDL_Quit();

  if (g) {
    g->running = false;

    delete g;
  }

  g = NULL;
}

bool game_running(Game *g) { return g->running; }

void handle_events(Game *g) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      g->running = false;
      break;
    }
  }
}

Uint64 last_time = SDL_GetTicks64();
Uint64 current_time = 0;
float delta = 0.0f;

float mass = 1200.0f;
float velocity = 0.0f;
float bounce_velocity = (1 / pow(mass, 0.35)) * 30000;
float radius = 20.0f;
SDL_FRect ball{(SCREEN_WIDTH - radius) / 2.0f, 20.0f, radius, radius};

void update(Game *g) {
  current_time = SDL_GetTicks64();
  delta = (current_time - last_time) / 1000.0f;

  float acceleration = GRAVITY * mass;

  velocity += acceleration * delta;

  float newh =
      ball.y + (velocity * delta) + (0.5 * acceleration * delta * delta);

  if (newh < 0) {
    newh = 0;
    velocity = bounce_velocity;
  } else if (newh > SCREEN_HEIGHT - radius) {
    newh = SCREEN_HEIGHT - radius;
    velocity = -bounce_velocity;
  }

  ball.y = newh;

  last_time = current_time;
}

void render(Game *g) {
  SDL_SetRenderDrawColor(g->renderer, 255, 255, 255, 255);
  SDL_RenderClear(g->renderer);

  SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
  SDL_RenderFillRectF(g->renderer, &ball);

  SDL_RenderPresent(g->renderer);
}
