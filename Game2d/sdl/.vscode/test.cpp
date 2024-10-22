#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* args[]) {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Tạo cửa sổ
    SDL_Window* window = SDL_CreateWindow("Red Box", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Tạo bề mặt (renderer)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Vòng lặp chính của game
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Xóa màn hình
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng
        SDL_RenderClear(renderer);

        // Vẽ hộp màu đỏ
        SDL_Rect box;
        box.x = 300; // Tọa độ x
        box.y = 200; // Tọa độ y
        box.w = 200; // Chiều rộng
        box.h = 150; // Chiều cao
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu đỏ
        SDL_RenderFillRect(renderer, &box);

        // Cập nhật màn hình
        SDL_RenderPresent(renderer);
    }

    // Giải phóng tài nguyên
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Delay(3000); // Chờ 3 giây trước khi đóng cửa sổ

    SDL_Quit();
    
    return 0;
}
