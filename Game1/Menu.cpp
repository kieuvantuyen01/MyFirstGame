#include "Menu.h"

Menu::Menu()
{
    state_ = SHOW_MENU;
    start_game_.SetText("LIBERATE THE SOUTH");
    advise_.SetText("ADVISE");
    exit_.SetText("EXIT");
    advise_content_.SetText("USE FOUR NAVIGATION KEYS TO MOVE ");
    advise_content_2.SetText("LEFT CLICK = SHOOT, RIGHT CLICK = JUMP");
    advise_content_3.SetText("Z, X = SHORT DIRECTION, C = CHANGE SHOOTING");
    back_.SetText("BACK");
    start_game_.SetColor(Text::WHITE_TEXT);
    advise_.SetColor(Text::WHITE_TEXT);
    exit_.SetColor(Text::WHITE_TEXT);
    advise_content_.SetColor(Text::WHITE_TEXT);
    advise_content_2.SetColor(Text::WHITE_TEXT);
    advise_content_3.SetColor(Text::WHITE_TEXT);
    back_.SetColor(Text::BLACK_TEXT);
    is_show_ = true;
}

Menu::~Menu()
{

}

void Menu::CreateText(TTF_Font * font, SDL_Renderer * screen)
{
    start_game_.CreateText(screen, font);
    advise_.CreateText(screen, font);
    exit_.CreateText(screen, font);
    advise_content_.CreateText(screen, font);
    advise_content_2.CreateText(screen, font);
    advise_content_3.CreateText(screen, font);
    back_.CreateText(screen, font);
}

void Menu::SetPostionText()
{
    SDL_Rect menu_pos = this -> GetRect();
    start_game_.setRect(menu_pos.x + 500, menu_pos.y + 400);
    advise_.setRect(menu_pos.x + 580, menu_pos.y + 450);
    exit_.setRect(menu_pos.x + 600, menu_pos.y + 500);
    advise_content_.setRect(menu_pos.x + 200, menu_pos.y + 350);
    advise_content_2.setRect(menu_pos.x + 200, menu_pos.y + 400);
    advise_content_3.setRect(menu_pos.x + 200, menu_pos.y + 450);
    back_.setRect(menu_pos.x + 600, menu_pos.y + 500);
}

void Menu::CheckEvents(SDL_Event events, bool & is_quit, bool & is_show_score)
{
    int x = events.motion.x;
    int y = events.motion.y;
    if (state_ == SHOW_MENU)
    {
        if (SDLCommonFunc::isInside(x, y, start_game_.GetRect())) //kiem tra ve chuot khi focus
        {
            start_game_.SetColor(Text::RED_TEXT);
            if (events.motion.type == SDL_MOUSEBUTTONDOWN)
            {
                is_show_ = false;
            }
        }
        else
        {
            start_game_.SetColor(Text::WHITE_TEXT);
            if (SDLCommonFunc::isInside(x, y, exit_.GetRect()))
            {
                exit_.SetColor(Text::RED_TEXT);
                if (events.motion.type == SDL_MOUSEBUTTONDOWN)
                {
                    is_show_ = false;
                    is_quit = true;
                    is_show_score = false;
                }
            }
            else
            {
                exit_.SetColor(Text::WHITE_TEXT);
                if (SDLCommonFunc::isInside(x, y, advise_.GetRect()))
                {
                    advise_.SetColor(Text::RED_TEXT);
                    if (events.motion.type == SDL_MOUSEBUTTONDOWN)
                    {
                        state_ = SHOW_HELP;
                    }
                }
                else
                {
                    advise_.SetColor(Text::WHITE_TEXT);
                }
            }
        }
    }
    else if (state_ == SHOW_HELP)
    {
        if (SDLCommonFunc::isInside(x, y, back_.GetRect()))
        {
            back_.SetColor(Text::RED_TEXT);
            if (events.motion.type == SDL_MOUSEBUTTONDOWN)
            {
                state_ = SHOW_MENU;
            }
        }
        else
        {
            back_.SetColor(Text::BLACK_TEXT);
        }
    }

}

void Menu::RenderMenu(SDL_Renderer * des)
{
    switch (state_)
    {
    case SHOW_MENU:
    {
        Render(des);
        start_game_.Render(des);
        advise_.Render(des);
        exit_.Render(des);
        break;
    }
    case SHOW_HELP:
    {
        Render(des);
        advise_content_.Render(des);
        advise_content_2.Render(des);
        advise_content_3.Render(des);
        back_.Render(des);
        break;
    }
    default:
        break;
    }
}
