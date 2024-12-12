#include "TextureHandle.h"
TextureHandle::TextureHandle(SDL_Renderer *renderer, const char *TTF_FILE, const int size, SDL_Color color, int style)
{
    this->renderer = renderer;
    this->font = TTF_OpenFont(TTF_FILE, size);
    TTF_SetFontSize(this->font, size);
    TTF_SetFontStyle(this->font, TTF_STYLE_NORMAL);
    this->color = color;
}

bool TextureHandle::LoadText(char *text)
{
    strcpy(this->text, text);
    return true;
}
bool TextureHandle::ShowText()
{
    SDL_Rect DesRect{500, 500, 100, 100};
    TextureHandle::ShowTextOnRect(DesRect);
    return true;
}
bool TextureHandle::ShowTextOnRect(SDL_Rect &DesRect)
{
    SDL_Surface *Tmp_Surface = TTF_RenderUTF8_Blended(this->font, this->text, this->color);
    this->texture = SDL_CreateTextureFromSurface(this->renderer, Tmp_Surface);
    // DesRect.h = Tmp_Surface->h;
    // DesRect.w = Tmp_Surface->w;
    // DesRect.x = 200;
    // DesRect.y = 720 - Tmp_Surface->h - 100;
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderCopy(this->renderer, this->texture, NULL, &DesRect);
    SDL_RenderPresent(this->renderer);
    SDL_FreeSurface(Tmp_Surface);
}

bool TextureHandle::Clear()
{
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);
}

TextureHandle::~TextureHandle()
{
    SDL_DestroyTexture(this->texture);
    TTF_CloseFont(this->font);
}