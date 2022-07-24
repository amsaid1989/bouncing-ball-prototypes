#include "Game.h"
#include "Ball.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdio.h>

Ball b{
    20.0f,                            // radius
    5.0f,                             // mass
    0.0f,                             // v0
    0.0f,                             // v
    SDL_GetTicks(),                   // t0
    SDL_GetTicks(),                   // t
    50.0f,                            // h0
    0.75f,                            // rho
    {(SCREEN_WIDTH - 20) / 2, 50.0f}, // position
    DOWN                              // direction
};

void init_game(Game &g) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialise SDL\n");
    g.running = false;
  }

  g.window = SDL_CreateWindow("Bouncy Ball", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!g.window) {
    SDL_Log("Failed to create window: %s\n", SDL_GetError());
    g.running = false;
    return;
  }

  g.renderer = SDL_CreateRenderer(
      g.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!g.renderer) {
    SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
    g.running = false;
    return;
  }

  g.running = true;
}

void handle_events(Game &g) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      g.running = false;
      break;
    }
  }
}

void update(Game &g) { move_ball(b); }

void render(const Game &g) {
  SDL_SetRenderDrawColor(g.renderer, 255, 255, 255, 255);
  SDL_RenderClear(g.renderer);

  render_ball(g.renderer, b);

  SDL_RenderPresent(g.renderer);
}

void close_game(Game &g) {
  g.running = false;

  SDL_DestroyRenderer(g.renderer);
  g.renderer = NULL;

  SDL_DestroyWindow(g.window);
  g.window = NULL;

  SDL_Quit();
}
