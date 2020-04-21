
/* LOP XU LY THONG SO GAME */

#ifndef DATA_GAME_H
#define DATA_GAME_H

#include "BaseObject.h"
#include "GeneralFunction.h"

class DataGame : public BaseObject
{
public:
    DataGame();
    ~DataGame();

    void SetNumLife(const int& num) {number_life_ = num;}
    void SetPosition(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void InitCrease();
    void Decrease();

private:
    int number_life_;
    std::vector<int> pos_list_;

};

class PlayerTorch : public BaseObject
{
public:
    PlayerTorch();
    ~PlayerTorch();

    void Init(SDL_Renderer* screen);
    void SetPosition(const int& x, const int& y) {x_pos_ = x, y_pos_ = y;};
    void Show(SDL_Renderer* screen);


private:
    int x_pos_;
    int y_pos_;
};


#endif // DATA_GAME_H
