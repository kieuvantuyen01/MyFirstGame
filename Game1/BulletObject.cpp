#include<random>
#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = GRENADE_BULLET;
}

BulletObject::~BulletObject()
{

}
unsigned int BulletObject::GetRandomBullet(int &tmp)
{
    if (tmp+1 > 3) tmp = 0;
    return BulletType(tmp);
}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    if (bullet_type_ == TANK_BULLET)
    {
        ret = LoadImg("img/tank_bullet.png", des);
    }
    else if (bullet_type_ == GRENADE_BULLET)
    {
        ret = LoadImg("img/grenade_bullet.png", des);
    }
    else if (bullet_type_ == MINE_BULLET)
    {
        ret = LoadImg("img/mine_bullet.png", des);
    }
    else
    {
        ret = LoadImg("img/player_bullet.png", des);
    }
    return ret;
}
void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_dir_ == DIR_RIGHT)
    {
        rect_.x += x_val_; // vi tri cua cac doi tuong ke thua trong baseObject
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT)
    {
        rect_.x -= x_val_; // vi tri cua cac doi tuong ke thua trong baseObject
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP)
    {
        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }

        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }

        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_DOWN_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }

        rect_.y += y_val_;
        if (rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_DOWN_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }

        rect_.y += y_val_;
        if (rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
}
