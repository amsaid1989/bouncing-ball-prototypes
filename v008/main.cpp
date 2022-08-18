#include "Game.h"
#include "defer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("STARTING GAME\n");

  int exit_code = EXIT_SUCCESS;

  Game g;
  bool game_initialised = init_game(g);
  defer_ref(close_game(g));

  if (!game_initialised) {
    printf("Failed to initialise game\n");
    exit_code = EXIT_FAILURE;
  }

  while (g.running) {
    handle_events(g);
    update(g);
    render(g);
  }

  return exit_code;
}
