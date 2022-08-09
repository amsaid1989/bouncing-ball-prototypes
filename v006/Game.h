#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;
  SDL_Texture *ball_texture;
  Uint32 last_time;
  Uint32 current_time;
  float delta;
};

bool init_game(Game &g);
void close_game(Game &g);
void handle_events(Game &g);
void update(Game &g);
void render(const Game &g);

#endif // !GAME_H
