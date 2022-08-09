#include "Game.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("STARTING GAME\n");

  int exit_code = EXIT_SUCCESS;

  Game g;

  if (!init_game(g)) {
    printf("Failed to initialise game\n");
    exit_code = EXIT_FAILURE;
  }

  while (g.running) {
    handle_events(g);
    update(g);
    render(g);
  }

  close_game(g);

  return exit_code;
}
