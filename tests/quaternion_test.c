// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#define MICRO_LA_IMPLEMENTATION
#include "../micro-la.h"

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>

#define WINDOW_NAME   "quaternion test"
#define WINDOW_WIDTH  500
#define WINDOW_HEIGHT 500
#define WINDOW_FLAGS  0

int main(void)
{
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  
  bool ret = SDL_CreateWindowAndRenderer(WINDOW_NAME, WINDOW_WIDTH,
                                         WINDOW_HEIGHT, WINDOW_FLAGS,
                                         &window, &renderer);
  if (!ret)
  {
    fprintf(stderr, "Error Creating SDL Window: %s\n", SDL_GetError());
    return 1;
  }

  Vec2f vec = (Vec2f){ .x = 100, .y = 0 };
  
  while(1)
  {  
    if (SDL_PollEvent(&event))
    {
      if (SDL_EVENT_KEY_DOWN == event.type)
      {
        if (event.key.key == 'q' || event.key.key == 0x1b /* ESC */)
          break;
        if (event.key.key == 'j')
          vec = Vec2f_translate(vec, (Vec2f) { .x = 0.0f, .y = 10.0f });
        if (event.key.key == 'k')
          vec = Vec2f_translate(vec, (Vec2f) { .x = 0.0f, .y = -10.0f });
        if (event.key.key == 'h')
          vec = Vec2f_translate(vec, (Vec2f) { .x = -10.0f, .y = 0.0f });
        if (event.key.key == 'l')
          vec = Vec2f_translate(vec, (Vec2f) { .x = 10.0f, .y = 0.0f });
        if (event.key.key == 'z')
          vec = Vec2f_scale(vec, (Vec2f) { .x = 1.1f, .y = 1.1f });
        if (event.key.key == 'x')
          vec = Vec2f_scale(vec, (Vec2f) { .x = 0.9f, .y = 0.9f });
        if (event.key.key == 'r')
          vec = Vec2f_rotate(vec, (3.14 / 360.0) * 5); // 5 degrees
        if (event.key.key == 'e')
          vec = Vec2f_rotate(vec, (-3.14 / 360.0) * 5);
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    if (!SDL_RenderClear(renderer))
    {
      fprintf(stderr, "Error Clearing SDL Window: %s\n", SDL_GetError());    
      goto cleanup;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if (!SDL_RenderLine(renderer,
                        WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f,
                        WINDOW_WIDTH / 2.0f + vec.x, WINDOW_HEIGHT / 2.0f + vec.y))
    {
      fprintf(stderr, "Error Rendering line: %s\n", SDL_GetError());    
      goto cleanup;
    }

    if (!SDL_RenderPresent(renderer))
    {
      fprintf(stderr, "Error Rendering SDL Window: %s\n", SDL_GetError());    
      goto cleanup;
    }
  }

 cleanup:

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
