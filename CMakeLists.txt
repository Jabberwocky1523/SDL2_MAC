cmake_minimum_required(VERSION 3.20)
project(cpp_sdl2)

set(CMAKE_CXX_STANDARD 11)


set(SDL_H /opt/homebrew/Cellar/sdl2/2.30.10/include)
set(SDL_IMG /opt/homebrew/Cellar/sdl2_image/2.8.2_2/include) 
set(SDL_TTF /opt/homebrew/Cellar/sdl2_ttf/2.22.0/include) 
include_directories(${SDL_H}) # 添加SDL头文件搜索路径
include_directories(${SDL_IMG})
include_directories(${SDL_TTF} TextureHandle)
file(GLOB_RECURSE TextureHandleCPP ./TextureHandle/*.cpp)
set(SDL_LIB /opt/homebrew/Cellar/sdl2/2.30.10/lib/libSDL2-2.0.0.dylib)
set(SDL_LIB_IMG /opt/homebrew/Cellar/sdl2_image/2.8.2_2/lib/libSDL2_image.dylib)
set(SDL_LIB_TTF /opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib/libSDL2_ttf.dylib) 
link_libraries(${SDL_LIB}) # 增加SDL链接库目录
link_libraries(${SDL_LIB_IMG})
link_libraries(${SDL_LIB_TTF})


add_executable(cpp_sdl2 script.cpp ${TextureHandleCPP})


