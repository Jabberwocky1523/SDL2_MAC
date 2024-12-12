#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_W 800
#define WINDOW_H 640

#undef main
int main(int argc, char *argv[])
{
    /*SDL初始化*/
    SDL_Init(SDL_INIT_VIDEO);
    /*TTF初始化*/
    TTF_Init();
    /*创建窗口*/
    SDL_Window *window = SDL_CreateWindow("SDL SHOW TEXT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    /*创建渲染器*/
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    /*设置渲染器颜色*/
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    /*清空渲染器*/
    SDL_RenderClear(render);
    /*打开字库*/
    TTF_Font *ttffont = TTF_OpenFont("Test.ttf", 50);
    if (ttffont == NULL)
    {
        printf("simkai.ttf open failed\n");
        return 0;
    }

    /*字体颜色RGBA*/
    SDL_Color color = {52, 203, 120, 255};
    SDL_Color bgColor = {33, 33, 33, 255};

    /*设置字体大小*/
    TTF_SetFontSize(ttffont, 60);
    /*字体加粗*/
    TTF_SetFontStyle(ttffont, TTF_STYLE_NORMAL);
    /*创建字体显示表面*/
    SDL_Surface *text1_surface = TTF_RenderUTF8_Blended(ttffont, "Hello,SDL!", color);
    /*创建纹理*/
    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, text1_surface);
    /*将surface拷贝到渲染器*/
    SDL_Rect dstrect;
    dstrect.x = WINDOW_W / 2 - text1_surface->w / 2; /*显示的起始位置*/
    dstrect.y = 100;                                 /*显示的起始位置*/
    dstrect.w = text1_surface->w;                    /*显示的宽度*/
    dstrect.h = text1_surface->h;                    /*显示的高度*/

    /*创建字体显示表面*/
    // SDL_Surface *text1_surface = TTF_RenderUTF8_Blended(ttffont, "Hello,SDL!", color);
    Uint16 msg[10] = {0x4F60, 0x597D, ',', 'T', 'T', 'F', 0}; //=Unicode 编码:你好
    SDL_Surface *text2_surface = TTF_RenderUNICODE_Solid(ttffont, msg, color);
    /*创建纹理*/
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(render, text2_surface);
    /*将surface拷贝到渲染器*/
    SDL_Rect dstrect2;
    dstrect2.x = WINDOW_W / 2 - text2_surface->w / 2; /*显示的起始位置*/
    dstrect2.y = 180;                                 /*显示的起始位置*/
    dstrect2.w = text2_surface->w;                    /*显示的宽度*/
    dstrect2.h = text2_surface->h;                    /*显示的高度*/

    bool bQuit = false;
    SDL_Event windowEvent;
    while (!bQuit)
    {
        while (SDL_PollEvent(&windowEvent))
        {
            switch (windowEvent.type)
            {
            case SDL_QUIT:
                bQuit = true;
                break;
            default:
                break;
            }
        }

        SDL_RenderClear(render);
        SDL_RenderCopy(render, texture, NULL, &dstrect);
        SDL_RenderCopy(render, texture2, NULL, &dstrect2);
        SDL_RenderPresent(render);
    }

    SDL_FreeSurface(text1_surface); /*释放surface*/
    SDL_DestroyTexture(texture);    /*释放纹理*/
    TTF_CloseFont(ttffont);
    TTF_Quit();

    return 0;
}