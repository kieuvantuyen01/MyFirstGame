#ifndef MENU_H_
#define MENU_H_

#include "CommonFunc.h"
#include "Text.h"

class Menu : public BaseObject
{
public:
    bool is_show_;
    Menu();
    ~Menu();
    enum STATE_
    {
        SHOW_MENU,
        SHOW_HELP
    };
    void CreateText(TTF_Font* font,SDL_Renderer* screen);
    void SetPostionText();
    void RenderMenu(SDL_Renderer* des);
    void CheckEvents(SDL_Event events, bool& is_quit, bool& is_show_score);
private:
    int state_;
    Text start_game_;
    Text help_;
    Text quit_;
    Text help_content_;
    Text help_content_2;
    Text help_content_3;
    Text back_;
};

#endif
