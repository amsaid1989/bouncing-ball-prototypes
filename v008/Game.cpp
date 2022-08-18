#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "constants.h"
#include "ui.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

INTERNAL_LINKAGE Ball gBall;
INTERNAL_LINKAGE Paddle gPaddle;

bool init_game(Game &g) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialise SDL\n");
    return false;
  }

  g.game_window.window = SDL_CreateWindow(
      "Bouncing Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

  if (TTF_Init() < 0) {
    printf("Failed to initialise SDL_ttf\n");
    return false;
  }

  g.game_font = load_font("DynaPuff-Medium.ttf", 36);
  if (!g.game_font) {
    printf("Failed to load font\n");
    return false;
  }

  srand(SDL_GetTicks());

  g.started = false;
  g.running = true;
  g.game_over = false;
  g.last_time = SDL_GetTicks();
  g.current_time = 0;
  g.delta = 0.0f;
  g.score = 0;

  init_ball(gBall, 20.0f, Ball::MAX_MASS, 25000.0f, g.game_window.width);

  gPaddle.width = g.game_window.width * 0.5f;
  gPaddle.height = 60.0f;
  gPaddle.x = (g.game_window.width - gPaddle.width) / 2;
  gPaddle.y = g.game_window.height - gPaddle.height - 50;
  gPaddle.mousex = (gPaddle.x / g.game_window.width) * SCREEN_WIDTH * 2;
  gPaddle.mousey = (gPaddle.y / g.game_window.height) * SCREEN_HEIGHT;
  gPaddle.prev_x = -1;
  gPaddle.prev_y = -1;

  return true;
}

void close_game(Game &g) {
  destroy_ui();

  close_font(g.game_font);

  TTF_Quit();

  SDL_DestroyTexture(g.ball_texture);
  g.ball_texture = NULL;

  IMG_Quit();

  SDL_DestroyRenderer(g.game_window.renderer);
  g.game_window.renderer = NULL;

  SDL_DestroyWindow(g.game_window.window);
  g.game_window.window = NULL;

  SDL_Quit();

  g.running = false;

  printf("GAME CLOSED\n");
}

void handle_events(Game &g) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      g.running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_RETURN && !g.started) {
        g.started = true;
      }
      break;
    }

    handle_paddle_events(gPaddle, event);
  }
}

void update(Game &g) {
  g.current_time = SDL_GetTicks();
  // g.delta = (g.current_time - g.last_time) / 1000.0f;
  g.delta = 1.0f / 60.0f;

  if (g.started) {
    if (g.score > 0 && g.score % 5 == 0 && !gBall.mass_changed) {
      change_ball_mass(gBall, gBall.mass - 100.0f, g.game_window.width);
    } else if (g.score % 5 != 0) {
      gBall.mass_changed = false;
    }

    if (move_ball(gBall, gPaddle, g.game_window.width, g.game_window.height,
                  g.score, g.delta)) {
      g.score += 1;
    }
    move_paddle(gPaddle, g.game_window.width);

    if (gBall.dead) {
      g.game_over = true;
    }
  }

  g.last_time = g.current_time;
}

void render(const Game &g) {
  SDL_SetRenderDrawColor(g.game_window.renderer, 255, 255, 255, 255);
  SDL_RenderClear(g.game_window.renderer);

  render_ball(gBall, g.game_window.width, g.game_window.height,
              g.game_window.renderer, g.ball_texture);

  render_paddle(gPaddle, g.game_window.width, g.game_window.height,
                g.game_window.renderer);

  render_score(g.game_window.renderer, g.game_window.width,
               g.game_window.height, g.game_font, g.score);

  if (!g.started) {
    render_start_screen(g.game_window.renderer, g.game_window.width,
                        g.game_window.height, g.game_font);
  }

  if (g.game_over) {
    render_game_over(g.game_window.renderer, g.game_window.width,
                     g.game_window.height, g.game_font);
  }

  SDL_RenderPresent(g.game_window.renderer);
}
