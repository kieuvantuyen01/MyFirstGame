#ifndef DATA_GAME_H_
#define DATA_GAME_H_

#include "BaseObject.h"
#include "CommonFunc.h"

class DataGame : public BaseObject
{
public:
    DataGame();
    ~DataGame();

    void SetNum(const int& num) {number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);// thiet lap vi tri ban dau

    void InitCrease();
    void Decrease();

private:
    int number_; // so mang
    std::vector<int> pos_list_;

};

class PlayerTorch : public BaseObject
{
public:
    PlayerTorch();
    ~PlayerTorch();

    void Init(SDL_Renderer* screen);
    void SetPos(const int& x, const int& y) {x_pos_ = x, y_pos_ = y;};
    void Show(SDL_Renderer* screen);


private:
    int x_pos_;
    int y_pos_;
};


#endif // DATA_GAME_H_
