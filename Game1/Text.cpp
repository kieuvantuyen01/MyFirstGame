
/*LOP XU LY HIEN THI CHU*/

#include "Text.h"

Text::Text()
{

}

Text::~Text()
{

}

bool Text::CreateText( SDL_Renderer* screen, TTF_Font* font)
{
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, text_val_.c_str(), text_color_);
	if(loadedSurface == NULL)
    {
        return false;
    }
	SetObject(SDL_CreateTextureFromSurface(screen, loadedSurface));
	if(this->GetObject() == NULL)
    {
        return false;
    }
	this->SetWidthHeight(loadedSurface->w, loadedSurface->h);

	SDL_FreeSurface(loadedSurface);
	return true;
}

bool Text::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text_val_.c_str(), text_color_);
    if (text_surface)
    {
        texture_ = SDL_CreateTextureFromSurface(screen, text_surface);
        width_ = text_surface->w;
        height_ = text_surface->h;

        SDL_FreeSurface(text_surface);
    }

    return texture_!= NULL;
}

//Tuong tu voi LoadFromRenderText
void Text::RenderText(SDL_Renderer* screen,
                    int xp, int yp,
                    SDL_Rect* clip,
                    double angle,
                    SDL_Point* center,
                    SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = {xp, yp, width_, height_};
    if (clip != NULL)
    {
        renderQuad.w = clip->h;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);
}

void Text::Free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;
}

void Text::SetColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0};
        text_color_ = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = {255, 255, 255};
        text_color_ = color;
    }
    else if (type == BLACK_TEXT)
    {
        SDL_Color color = {0, 0, 0};
        text_color_ = color;
    }
    else if (type == YELLOW_TEXT)
    {
        SDL_Color color = {249, 244, 0};
        text_color_ = color;
    }
}
