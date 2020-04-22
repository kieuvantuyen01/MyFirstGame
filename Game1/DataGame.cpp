
/* LOP XU LY THONG SO GAME */

#include "DataGame.h"

/*Xu ly mang cua nhan vat chinh*/
DataGame::DataGame()
{
    number_life_ = 0;
}

DataGame::~DataGame()
{

}

void DataGame::SetPosition(const int& xp)
{
    pos_list_.push_back(xp);
}

void DataGame::Init(SDL_Renderer* screen)
{
    bool ret = LoadImg("assert/player_life.png", screen);
    if (!ret)
    {
        return;
    }
    number_life_ = 3;
    if (pos_list_.size() > 0)
    {
        pos_list_.clear();
    }
    SetPosition(160);
    SetPosition(200);
    SetPosition(240);
}

void DataGame::Show(SDL_Renderer* screen)
{
    for (int i = 0; i < pos_list_.size(); i++)
    {
        rect_.x = pos_list_.at(i);
        rect_.y = 50;
        Render(screen);
    }
}

void DataGame::Decrease()
{
    number_life_ --;
    pos_list_.pop_back();
}

void DataGame::InitCrease()
{
    number_life_ ++;
    int last_pos = pos_list_.back();
    last_pos += 40;
    pos_list_.push_back(last_pos);

}

/*Xu ly so Duoc*/

PlayerTorch::PlayerTorch()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

PlayerTorch::~PlayerTorch()
{

}

void PlayerTorch::Init(SDL_Renderer* screen)
{
    bool ret = LoadImg("assert/torch.png", screen);
    if (!ret)
    {
        return;
    }
}

void PlayerTorch::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(screen);
}
