
/*LOP XU LY HIEN THI CHU*/

#ifndef TEXT_H
#define TEXT_H

#include "GeneralFunction.h"
#include "BaseObject.h"

class Text:public BaseObject
{
public:
	Text();
	~Text();

	bool CreateText(SDL_Renderer* screen, TTF_Font* font);
	void RenderText(SDL_Renderer* screen,
                    int xp, int yp,
                    SDL_Rect* clip = NULL,
                    double angle = 0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void SetText(const std::string& text) {text_val_ = text;}
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(int type);

	int GetWidth() const {return width_;}
    int GetHeight() const {return height_;}

    void Free();

    enum COlOR
    {
		RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
        YELLOW_TEXT = 3,
	};

private:
    int width_;
    int height_;

	std::string text_val_;
	SDL_Color text_color_;

    SDL_Texture* texture_;
};

#endif // TEXT_H
