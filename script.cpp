#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_ttf.h>
#include "TextureHandle/TextureHandle.h"
#define SDL_H_
#define W 1280
#define H 720
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("SDL SHOW TEXT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
    /*创建渲染器*/
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);
    SDL_Color color{52, 203, 120, 255};
    TextureHandle TH(render, "Test.ttf", 30, color, TTF_STYLE_NORMAL);
    TH.LoadText("123");
    TH.ShowText();
    // TH.LoadText("1233");
    // TH.ShowText();
    SDL_Event event;
    SDL_Rect a{0, 0, 100, 100};
    int temp = 1;
    while (temp)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                temp = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                TH.Clear();
                SDL_Delay(500);
                TH.LoadText("1233");
                TH.ShowTextOnRect(a);
                break;
            default:
                break;
            }
        }
    }
    TTF_Quit();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
}
