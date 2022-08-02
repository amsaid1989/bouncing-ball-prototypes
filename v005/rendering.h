#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>

struct Point {
  float x;
  float y;
};

void draw_circle(SDL_Renderer *renderer, Point centre, float radius);
void draw_circle_from_texture(SDL_Renderer *renderer, SDL_Texture *texture,
                              Point centre, float radius);

#endif // !RENDERING_H
