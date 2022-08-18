#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Window {
  float width;
  float height;
  SDL_Window *window;
  SDL_Renderer *renderer;
};

struct Game {
  Window game_window;
  bool started;
  bool running;
  bool game_over;
  SDL_Texture *ball_texture;
  TTF_Font *game_font;
  Uint32 last_time;
  Uint32 current_time;
  float delta;
  int score;
};

bool init_game(Game &g);
void close_game(Game &g);
void handle_events(Game &g);
void update(Game &g);
void render(const Game &g);

#endif // !GAME_H
