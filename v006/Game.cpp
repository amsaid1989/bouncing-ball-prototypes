#include "Game.h"
#include "Ball.h"
#include "constants.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

Ball gBall;

bool init_game(Game &g) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialise SDL\n");
    return false;
  }

  g.window = SDL_CreateWindow("Bouncy Ball", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!g.window) {
    printf("Failed to create window! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  g.renderer = SDL_CreateRenderer(
      g.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!g.renderer) {
    printf("Failed to create renderer! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    printf("Failed to initialise SDL_image\n");
    return false;
  }

  g.ball_texture = IMG_LoadTexture(g.renderer, "circle.png");
  if (!g.ball_texture) {
    printf("Failed to load texture\n");
    return false;
  }

  srand(SDL_GetTicks());

  g.running = true;
  g.last_time = SDL_GetTicks();
  g.current_time = 0;

  init_ball(gBall, 20.0f, Ball::MAX_MASS, 5000.0f);

  return true;
}

void close_game(Game &g) {
  SDL_DestroyTexture(g.ball_texture);
  g.ball_texture = NULL;

  IMG_Quit();

  SDL_DestroyRenderer(g.renderer);
  g.renderer = NULL;

  SDL_DestroyWindow(g.window);
  g.window = NULL;

  SDL_Quit();

  g.running = false;
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

void update(Game &g) {
  g.current_time = SDL_GetTicks();
  g.delta = (g.current_time - g.last_time) / 1000.0f;

  move_ball(gBall, g.delta);

  g.last_time = g.current_time;
}

void render(const Game &g) {
  SDL_SetRenderDrawColor(g.renderer, 255, 255, 255, 255);
  SDL_RenderClear(g.renderer);

  render_ball(g.renderer, g.ball_texture, gBall);

  SDL_RenderPresent(g.renderer);
}
