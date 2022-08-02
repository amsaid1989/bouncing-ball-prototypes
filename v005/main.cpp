#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

int main(int argc, char *argv[]) {
  Game *g = init_game();

  if (g) {
    while (game_running(g)) {

      handle_events(g);

      update(g);

      render(g);
    }
  }

  close_game(g);

  return 0;
}
