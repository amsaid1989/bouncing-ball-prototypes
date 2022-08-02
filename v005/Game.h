#ifndef GAME_H
#define GAME_H

struct Game;

Game *init_game();
void close_game(Game *);
bool game_running(Game *);
void handle_events(Game *);
void update(Game *);
void render(Game *);

#endif // !GAME_H
