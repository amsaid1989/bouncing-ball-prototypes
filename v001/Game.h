#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;
};

void init_game(Game &g);
void handle_events(Game &g);
void update(Game &g);
void render(const Game &g);
void close_game(Game &g);

#endif // !GAME_H
