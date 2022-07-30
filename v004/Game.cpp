#include "Game.h"
#include "constants.h"
#include "rendering.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <cstdlib>
#include <math.h>

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;
  SDL_Texture *circle_texture;
};

enum Direction {
  NEG,
  NONE,
  POS,

  TOTAL
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

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    printf("Failed to initialise SDL_image\n");
    return NULL;
  }

  SDL_Texture *texture = IMG_LoadTexture(renderer, "circle.png");
  if (!texture) {
    printf("Failed to load texture\n");
    return NULL;
  }

  srand(SDL_GetTicks());

  return new Game{window, renderer, true, texture};
}

void close_game(Game *g) {
  SDL_DestroyTexture(g->circle_texture);
  g->circle_texture = NULL;

  IMG_Quit();

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

int get_direction_value(Direction dir) { return (int)floor((float)dir - 0.5); }
Direction get_random_direction() { return (Direction)(rand() % (int)TOTAL); }

Uint64 last_time = SDL_GetTicks();
Uint64 current_time = 0;
float delta = 0.0f;

float mass = 1000.0f;
float initial_velocity = (1 / pow(mass, 0.35)) * 30000;
float xvel = 0.0f;
float yvel = initial_velocity;
float radius = 80.0f;
Direction ydir = POS;
Direction xdir = NONE;
SDL_FRect ball{(SCREEN_WIDTH - radius) / 2.0f, 20.0f, radius, radius};

void update(Game *g) {
  current_time = SDL_GetTicks();
  delta = (current_time - last_time) / 1000.0f;

  float acceleration = GRAVITY * mass;

  yvel += acceleration * delta;

  float newY = ball.y + (yvel * delta) + (0.5 * acceleration * delta * delta);

  if (newY < 0) {
    newY = 0;
    xdir = get_random_direction();
    ydir = POS;
    yvel = get_direction_value(ydir) * initial_velocity;
  } else if (newY > SCREEN_HEIGHT - radius) {
    newY = SCREEN_HEIGHT - radius;
    xdir = get_random_direction();
    ydir = NEG;
    yvel = get_direction_value(ydir) * initial_velocity;
  }

  ball.y = newY;

  xvel = get_direction_value(xdir) * (initial_velocity / 4);

  float newX = ball.x + (xvel * delta);

  if (newX < 0) {
    newX = 0;
    xdir = POS;
  } else if (newX > SCREEN_WIDTH - radius) {
    newX = SCREEN_WIDTH - radius;
    xdir = NEG;
  }

  ball.x = newX;

  last_time = current_time;
}

void render(Game *g) {
  SDL_SetRenderDrawColor(g->renderer, 255, 255, 255, 255);
  SDL_RenderClear(g->renderer);

  draw_circle_from_texture(g->renderer, g->circle_texture, {ball.x, ball.y},
                           ball.w);

  SDL_RenderPresent(g->renderer);
}
