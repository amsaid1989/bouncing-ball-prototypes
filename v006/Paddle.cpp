#include "Paddle.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

void handle_paddle_events(Paddle &p, const SDL_Event &event,
                          float window_width) {
  if (event.type == SDL_MOUSEMOTION) {
    // The x value of the mouse motion is in pixels, but we need to make sure
    // that we get the value according to the window size in screen coordinates
    // in case the system supports high DPI
    p.x = ((float)event.motion.x / SCREEN_WIDTH) * window_width;
    p.x -= p.width / 2;

    if (p.x < 0) {
      p.x = 0;
    } else if (p.x > window_width - p.width) {
      p.x = window_width - p.width;
    }
  }
}

void move_paddle(Paddle &p) {}

void render_paddle(const Paddle &p, float window_width, float window_height,
                   SDL_Renderer *renderer) {
  SDL_FRect dest{p.x, window_height - p.height - 50, p.width, p.height};

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRectF(renderer, &dest);
}
