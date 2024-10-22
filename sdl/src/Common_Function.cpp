#include "../include/Common_Function.h"

SDL_Texture* SDLCommonFunc::LoadImage(std::string file_path, SDL_Renderer* renderer)
{
    SDL_Surface* load_image = IMG_Load(file_path.c_str());
    if (load_image == NULL)
    {
        std::cout << "Unable to load image " << file_path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return NULL;
    }

    // Convert SDL_Surface to SDL_Texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, load_image);
    if (texture == NULL)
    {
        std::cout << "Unable to create texture from " << file_path << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(load_image); // Free the surface after converting it to texture
    
    return texture;
}

void SDLCommonFunc::ApplyTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y)
{
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;

    // Query the texture to get its width and height
    SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);

    // Copy the texture to the renderer at the specified position
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}

void SDLCommonFunc::CleanUp()
{
    SDL_DestroyTexture(g_background); 
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
}