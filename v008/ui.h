#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TTF_Font *load_font(const char *filepath, int size);
void render_start_screen(SDL_Renderer *renderer, int window_width,
                         int window_height, TTF_Font *font);
void render_score(SDL_Renderer *renderer, int window_width, int window_height,
                  TTF_Font *font, int score);
void render_game_over(SDL_Renderer *renderer, int window_width,
                      int window_height, TTF_Font *font);
void destroy_ui();
void close_font(TTF_Font *font);

#endif // !UI_H
