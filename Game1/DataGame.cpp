#include "DataGame.h"

DataGame::DataGame()
{
    number_ = 0;
}

DataGame::~DataGame()
{

}

void DataGame::SetPos(const int& xp)
{
    pos_list_.push_back(xp);
}

void DataGame::Init(SDL_Renderer* screen)
{
    //bool ret =
    LoadImg("img/player_pw.png", screen);
//    if (!ret)
//    {
//        return;
//    }
    number_ = 3;
    if (pos_list_.size() > 0)
    {
        pos_list_.clear();
    }
    SetPos(160);
    SetPos(200);
    SetPos(240);
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
    number_ --;
    pos_list_.pop_back();
}

void DataGame::InitCrease()
{
    number_++;
    int last_pos = pos_list_.back();
    last_pos += 40;
    pos_list_.push_back(last_pos);

}

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
    bool ret = LoadImg("img/torch.png", screen);
}

void PlayerTorch::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(screen);
}
