
/*LOP XU LY MENU*/

#ifndef MENU_H
#define MENU_H

#include "GeneralFunction.h"
#include "Text.h"

class Menu : public BaseObject
{
public:
    bool is_show_;
    Menu();
    ~Menu();

    void CreateText(TTF_Font* font, SDL_Renderer* screen);
    void SetPostionText();
    void RenderMenu(SDL_Renderer* des);
    void CheckEvents(SDL_Event events, bool& is_quit, bool& is_show_score);

    enum ACTION_
    {
        SHOW_MENU,
        SHOW_ADVISE,
    };

private:
    int action_;

    Text start_game_;
    Text advise_;
    Text exit_;

    Text advise_content_;
    Text advise_content_2;
    Text advise_content_3;
    Text back_;

};

#endif // MENU_H
