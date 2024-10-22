#include "../include/Common_Function.h" 
#include "../include/MainObject.h"
#include "../include/BulletObject.h"   
#include "../include/ThreatesObject.h"

bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    g_window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == NULL)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* args[])
{
    if (!Init())
    {
        std::cout << "Failed to initialize!" << std::endl;
        return -1;
    }

    // Load background image
    g_background = SDLCommonFunc::LoadImage("bg1.png", g_renderer);
    if (g_background == NULL)
    {
        std::cout << "Failed to load background image!" << std::endl;
        return -1;
    }
    // Make MainObject
    MainObject human_object;
    human_object.SetRect(100, 200);

    bool ret = human_object.LoadImg("plane_fly.png", g_renderer);
    if (!ret)
    {
        return 0;
    }

    // Make ThreatObject
    ThreatObject* p_threat = new ThreatObject() ;
    ret = p_threat->LoadImg("af1.png",g_renderer) ;
    if(!ret)
    {
        return 0 ;
    }
    p_threat->SetRect(SCREEN_WIDTH,SCREEN_HEIGHT * 0.3) ;
    p_threat->set_x_val(1) ;

    bool quit = false;

    while (!quit)
    {
        SDL_RenderClear(g_renderer); 

        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                quit = true;
            }
            human_object.HandleInputAction(g_event,g_renderer);
            human_object.HandleMove(); 
            
        } 

            SDLCommonFunc::ApplyTexture(g_background, g_renderer, 0, 0); 
            human_object.Show(g_renderer);
            human_object.HandleBullet(g_renderer) ;
            p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT) ;
            p_threat->Show(g_renderer) ;
            
      

        SDL_RenderPresent(g_renderer); 
    }

    SDLCommonFunc::CleanUp();
    SDL_Quit();
    return 0;
}
