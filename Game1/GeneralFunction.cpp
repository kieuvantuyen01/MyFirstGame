
/* LOP XU LY CAC HAM CHUNG */

#include "GeneralFunction.h"
#include "BaseObject.h"
#include "Text.h"

bool SDLCommonFunc::isInside(int& x, int& y, SDL_Rect object)
{
	if(x >= object.x && x <= object.x+object.w && y >= object.y && y <= object.y + object.h)
    {
        return true;
    }
    return false;
}

void SDLCommonFunc::waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 &&
        (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
        {
            return;
        }
        SDL_Delay(100);
        SDL_Quit();
    }
}

int SDLCommonFunc::MakeRandValue(const int& val_)
{
    int rand_y_ = rand() % val_;
    if (rand_y_ > SCREEN_HEIGHT*2/3)
    {
        rand_y_ = SCREEN_HEIGHT*0.3;
    }
    return rand_y_;
}

bool SDLCommonFunc::CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Lay cac kich thuoc cua rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Lay cac kich thuoc cua rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //Neu bat ki canh nao cua A o phia ngoai B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //Neu khong co canh nao cua A o ngoai B
    return true;
}

