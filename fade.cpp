#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main2(int argc, char *argv[])
{
    // 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("Smooth Rectangle Fade In and Out", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    bool quit = false;
    SDL_Event e;
    float alpha = 0.0f;
    float alphaChange = 2.0f; // 控制淡入淡出的速度
    // 主循环
    while (!quit)
    {
        // 事件处理
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // 更新 alpha 值实现平滑的淡入淡出效果
        alpha += alphaChange;
        int oldAlpha = alpha;
        if (alpha >= 255.0f || alpha <= 0.0f)
        {
            alphaChange = -alphaChange;              // 反向改变
            alpha = std::clamp(alpha, 0.0f, 255.0f); // 确保 alpha 在范围内
        }

        // 清空屏幕
        SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

        // 设置矩形颜色和透明度
        SDL_SetRenderDrawColor(renderer, alpha, 0, 0, 255);
        SDL_RenderFillRect(renderer, &fillRect);

        // 更新屏幕
        SDL_RenderPresent(renderer);

        // 控制帧率
        SDL_Delay(16); // 约 60 帧每秒
    }

    // 释放资源并退出
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
