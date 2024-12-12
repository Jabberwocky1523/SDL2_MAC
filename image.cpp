#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_thread.h>
#define W 1280
#define H 720
SDL_Rect rect = {0, 0, 1280, 720};
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    IMG_Init(IMG_INIT_PNG);
    SDL_Window *win = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       W, H, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    if (NULL == win)
    {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return -1;
    }

    // 创建渲染器与清屏
    SDL_Renderer *rdr = SDL_CreateRenderer(win, -1, 0);
    if (NULL == rdr)
    {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        return -1;
    }
    // 渲染图片
    // 1. 导入图片
    SDL_Surface *img_surf = IMG_Load("./test.png"); // 1296*864

    if (NULL == img_surf)
    {
        SDL_Log("SDL_LoadBMP failed: %s", SDL_GetError());
        return -1;
    }
    SDL_SetWindowSize(win, img_surf->w, img_surf->h);

    // 2. 创建Texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rdr, img_surf);
    if (NULL == texture)
    {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        return -1;
    }
    SDL_SetRenderDrawColor(rdr, 0, 0, 0, 0);
    SDL_RenderClear(rdr);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    // SDL_SetTextureAlphaMod(texture, 128);
    // SDL_RenderCopy(rdr, texture, NULL, NULL);
    // SDL_SetTextureAlphaMod(texture, 255);
    // SDL_RenderCopy(rdr, texture, nullptr, nullptr);
    // 渲染呈现
    SDL_Event event;
    for (int i = 0; i <= 255; i++)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return -1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_SetTextureAlphaMod(texture, i);
                SDL_RenderCopy(rdr, texture, nullptr, nullptr);
                SDL_RenderPresent(rdr);
                break;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                event.type = SDL_QUIT;
                SDL_PushEvent(&event);
            }
        }
        SDL_SetTextureAlphaMod(texture, i);
        SDL_RenderCopy(rdr, texture, NULL, NULL);
        SDL_RenderPresent(rdr);
        SDL_Delay(20);
    }
    // SDL_SetRenderDrawColor(rdr, 255, 0, 0, 255);
    // SDL_RenderClear(rdr);
    // SDL_RenderPresent(rdr);

    // SDL_RenderClear(rdr);
    // SDL_SetRenderDrawColor(rdr, 255, 255, 255, 255);
    // SDL_RenderFillRect(rdr, &rect);
    // SDL_RenderPresent(rdr);
    while (true)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                event.type = SDL_QUIT;
                SDL_PushEvent(&event);
            }
        }
    }

    // 5. 销毁Texture
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(img_surf);
    SDL_DestroyRenderer(rdr);
    SDL_DestroyWindow(win);
    SDL_Quit();
    IMG_Quit();
    return 0;
}