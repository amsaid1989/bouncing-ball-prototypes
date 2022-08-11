#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

struct Paddle {
  float x;
  float y;
  float prev_x;
  float prev_y;
  float mousex;
  float mousey;
  float width;
  float height;
};

void handle_paddle_events(Paddle &p, const SDL_Event &event);
void move_paddle(Paddle &p, float window_width);
void render_paddle(const Paddle &p, float window_width, float window_height,
                   SDL_Renderer *renderer);

#endif // !PADDLE_H
