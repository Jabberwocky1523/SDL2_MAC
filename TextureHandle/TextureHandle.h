#ifndef SDL_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif
class TextureHandle
{
public:
    TextureHandle(SDL_Renderer *renderer, const char *TTF_FILE, const int size, SDL_Color color, int style);
    ~TextureHandle();
    bool LoadText(char *text);
    bool ShowText();
    bool ShowTextOnRect(SDL_Rect &DesRect);
    bool Clear();


    bool SetFontSize(int size);
    bool SetColor(SDL_Color color);
    bool SetBlendMode(SDL_BlendMode blend_mode);
    bool SetAlpha(Uint8 alpha);
    bool SetFontStyle(int style);
    SDL_Texture *GetTexture();
    TTF_Font *GetFont();

private:
    char *text = (char *)malloc(1028);
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Color color;
};