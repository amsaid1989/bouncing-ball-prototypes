#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  Game g;

  init_game(g);

  while (g.running) {
    handle_events(g);

    update(g);

    render(g);
  }

  close_game(g);

  return 0;
}
