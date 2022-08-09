#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "constants.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

INTERNAL_LINKAGE Ball gBall;
INTERNAL_LINKAGE Paddle gPaddle;

bool init_game(Game &g) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialise SDL\n");
    return false;
  }

  g.game_window.window = SDL_CreateWindow(
      "Bouncy Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
  if (!g.game_window.window) {
    printf("Failed to create window! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  int w;
  int h;
  SDL_GL_GetDrawableSize(g.game_window.window, &w, &h);
  g.game_window.width = (float)w;
  g.game_window.height = (float)h;

  g.game_window.renderer =
      SDL_CreateRenderer(g.game_window.window, -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!g.game_window.renderer) {
    printf("Failed to create renderer! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    printf("Failed to initialise SDL_image\n");
    return false;
  }

  g.ball_texture = IMG_LoadTexture(g.game_window.renderer, "circle.png");
  if (!g.ball_texture) {
    printf("Failed to load texture\n");
    return false;
  }

  srand(SDL_GetTicks());

  g.running = true;
  g.last_time = SDL_GetTicks();
  g.current_time = 0;
  g.delta = 0.0f;
  g.score = 0;

  init_ball(gBall, 20.0f, Ball::MAX_MASS, 20000.0f);

  gPaddle.width = g.game_window.width * 0.5f;
  gPaddle.height = 60.0f;
  gPaddle.x = (g.game_window.width - gPaddle.width) / 2;

  return true;
}

void close_game(Game &g) {
  SDL_DestroyTexture(g.ball_texture);
  g.ball_texture = NULL;

  IMG_Quit();

  SDL_DestroyRenderer(g.game_window.renderer);
  g.game_window.renderer = NULL;

  SDL_DestroyWindow(g.game_window.window);
  g.game_window.window = NULL;

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

    handle_paddle_events(gPaddle, event, g.game_window.width);
  }
}

void update(Game &g) {
  g.current_time = SDL_GetTicks();
  g.delta = (g.current_time - g.last_time) / 1000.0f;

  move_ball(gBall, g.game_window.width, g.game_window.height, g.score, g.delta);

  g.last_time = g.current_time;
}

void render(const Game &g) {
  SDL_SetRenderDrawColor(g.game_window.renderer, 255, 255, 255, 255);
  SDL_RenderClear(g.game_window.renderer);

  render_ball(gBall, g.game_window.width, g.game_window.height,
              g.game_window.renderer, g.ball_texture);

  render_paddle(gPaddle, g.game_window.width, g.game_window.height,
                g.game_window.renderer);

  SDL_RenderPresent(g.game_window.renderer);
}
