#include "rendering.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstdlib>

float square(float x) { return x * x; }

void draw_circle(SDL_Renderer *renderer, Point centre, float radius) {
  /**
   * A function to draw the outline of a circle using the Midpoint Circle
   * Drawing Algorithm (https://en.wikipedia.org/wiki/Midpoint_circle_algorithm)
   */

  float x = 0;
  float y = 0 - radius;

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // Draw the 4 poles
  SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y); // top
  SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x); // right
  SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y); // bottom
  SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x); // left

  for (x += 1; x <= abs(y); ++x) {
    float midpoint = y + 0.5;

    float p = square(x) + square(midpoint) - square(radius);

    if (p > 0) {
      ++y;
    }

    SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y);
    SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
    SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y);
    SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
    SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x);
    SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
    SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x);
    SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
  }
}

void draw_circle_from_texture(SDL_Renderer *renderer, SDL_Texture *texture,
                              Point centre, float radius) {
  int width;
  int height;

  SDL_QueryTexture(texture, NULL, NULL, &width, &height);

  SDL_FRect dest = {centre.x, centre.y, radius, radius};

  SDL_RenderCopyF(renderer, texture, NULL, &dest);
}
