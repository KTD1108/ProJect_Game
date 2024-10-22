#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600  ;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_renderer = NULL;
static SDL_Texture* g_background = NULL;
static SDL_Event g_event;

namespace SDLCommonFunc
{
    SDL_Texture* LoadImage(std::string file_path, SDL_Renderer* renderer) ;
    void ApplyTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y) ;
    void CleanUp() ;
}

#endif