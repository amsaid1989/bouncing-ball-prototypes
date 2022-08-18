#include "ui.h"
#include "constants.h"
#include "defer.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

struct UI {
  SDL_Texture *start_screen_texture;
  SDL_Texture *score_texture;
  SDL_Texture *game_over_texture;
} gUI;

TTF_Font *load_font(const char *filepath, int size) {
  return TTF_OpenFont(filepath, size);
}

SDL_Texture *create_text_texture(SDL_Renderer *renderer, const char *text,
                                 TTF_Font *font) {
  SDL_Color text_color{0, 0, 0, 255};

  SDL_Surface *surface = TTF_RenderText_Solid(font, text, text_color);
  defer_ref(SDL_FreeSurface(surface));

  if (!surface) {
    printf("Failed to create text surface\n");
    return NULL;
  }

  return SDL_CreateTextureFromSurface(renderer, surface);
}

void render_start_screen(SDL_Renderer *renderer, int window_width,
                         int window_height, TTF_Font *font) {
  const char *start_str = "PRESS ENTER TO START";

  gUI.start_screen_texture = create_text_texture(renderer, start_str, font);

  if (!gUI.start_screen_texture) {
    printf("Failed to create the start screen texture\n");
    return;
  }

  int text_w;
  int text_h;
  TTF_SizeText(font, start_str, &text_w, &text_h);

  text_w = (int)(((float)text_w / SCREEN_WIDTH) * window_width);
  text_h = (int)(((float)text_h / SCREEN_HEIGHT) * window_height);

  SDL_Rect dest{(window_width - text_w) / 2, (window_height - text_h) / 2,
                text_w, text_h};
  SDL_RenderCopy(renderer, gUI.start_screen_texture, NULL, &dest);
}

void render_score(SDL_Renderer *renderer, int window_width, int window_height,
                  TTF_Font *font, int score) {
  char score_str[20];
  sprintf(score_str, "Score: %d", score);

  gUI.score_texture = create_text_texture(renderer, score_str, font);

  if (!gUI.score_texture) {
    printf("Failed to create the score texture\n");
    return;
  }

  int text_w;
  int text_h;
  TTF_SizeText(font, score_str, &text_w, &text_h);

  text_w = (int)(((float)text_w / SCREEN_WIDTH) * window_width);
  text_h = (int)(((float)text_h / SCREEN_HEIGHT) * window_height);

  SDL_Rect dest{30, 10, text_w, text_h};
  SDL_RenderCopy(renderer, gUI.score_texture, NULL, &dest);
}

void render_game_over(SDL_Renderer *renderer, int window_width,
                      int window_height, TTF_Font *font) {
  const char *game_over_str = "GAME OVER";

  gUI.game_over_texture = create_text_texture(renderer, game_over_str, font);

  if (!gUI.game_over_texture) {
    printf("Failed to create the game over texture\n");
    return;
  }

  int text_w;
  int text_h;
  TTF_SizeText(font, game_over_str, &text_w, &text_h);

  text_w = (int)(((float)text_w / SCREEN_WIDTH) * window_width);
  text_h = (int)(((float)text_h / SCREEN_HEIGHT) * window_height);

  SDL_Rect dest{(window_width - text_w) / 2, (window_height - text_h) / 2,
                text_w, text_h};
  SDL_RenderCopy(renderer, gUI.game_over_texture, NULL, &dest);
}

void destroy_ui() {
  SDL_DestroyTexture(gUI.start_screen_texture);
  SDL_DestroyTexture(gUI.score_texture);
  SDL_DestroyTexture(gUI.game_over_texture);

  gUI.start_screen_texture = NULL;
  gUI.score_texture = NULL;
  gUI.game_over_texture = NULL;
}

void close_font(TTF_Font *font) {
  TTF_CloseFont(font);
  font = NULL;
}
