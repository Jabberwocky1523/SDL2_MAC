#include <SDL2/SDL.h>

#define W 1200
#define H 800

#undef main
int main2()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    SDL_Window *win = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       W, H, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    if (NULL == win)
    {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return -1;
    }

    // 在窗口上绘制一个矩形
    // 1. 获取与窗口关联的Surface
    SDL_Surface *surf = SDL_GetWindowSurface(win);
    if (NULL == surf)
    {
        SDL_Log("SDL_GetWindowSurface failed: %s", SDL_GetError());
        return -1;
    }

    // 2. 定义一个区域
    SDL_Rect rect = {200, 200, 50, 50};

    // 3. 在Surface上进行绘制
    // SDL_FillRect(surf, &rect, SDL_MapRGB(surf->format, 0, 255, 0));
    SDL_FillRect(surf, &rect, 0x00ff00);

    // 4. 将绘制的内容更新到屏幕上
    SDL_UpdateWindowSurface(win);

    SDL_Event event;

    int i = 1;
    while (true)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }

        SDL_FillRect(surf, &rect, 0x000000);
        rect.x += 2 * i;
        SDL_FillRect(surf, &rect, 0x00ff00);
        SDL_UpdateWindowSurface(win);
        SDL_Delay(10);
        if (rect.x > W - rect.w || rect.x < 0)
        {
            i = -1 * i;
        }
    }

    // 4. 释放Surface
    SDL_FreeSurface(surf);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}