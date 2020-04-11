
#ifndef TEXT_H_
#define TEXT_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class Text:public BaseObject
{
public:
	Text();
	~Text();
	enum COlOR{
		RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
        YELLOW_TEXT = 3,
	};
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void SetText(const std::string& text) {text_val_=text;}
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(int type);

	int GetWidth() const {return width_;}
    int GetHeight() const {return height_;}

    void Free();

	bool CreateText(SDL_Renderer* screen,TTF_Font* font);
	void RenderText(SDL_Renderer* screen,
                    int xp, int yp,
                    SDL_Rect* clip = NULL,
                    double angle = 0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	std::string text_val_;
	SDL_Color text_color_;
	int width_;
    int height_;
    SDL_Texture* texture_;
};

#endif
