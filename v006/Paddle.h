#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

struct Paddle {
  float x;
  float width;
  float height;
};

void handle_paddle_events(Paddle &p, const SDL_Event &event,
                          float window_width);
void move_paddle(Paddle &p);
void render_paddle(const Paddle &p, float window_width, float window_height,
                   SDL_Renderer *renderer);

#endif // !PADDLE_H
