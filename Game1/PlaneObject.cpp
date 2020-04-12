
#include "PlaneObject.h"

PlaneObject::PlaneObject()
{
    rect_.x = SCREEN_WIDTH;
    rect_.y = SCREEN_HEIGHT;
    rect_.w = WIDHT_PLANE;
    rect_.h = HEIGHT_PLANE;

    x_val_ = 0;
    y_val_ = 0;
}

PlaneObject::~PlaneObject()
{
    if (p_bullet_list_.size() > 0)
    {
        for (int i = 0; i < p_bullet_list_.size(); i++)
        {
            BulletObject* p_bullet = p_bullet_list_.at(i);
            if (p_bullet != NULL)
            {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
        p_bullet_list_.clear();
    }
}

void PlaneObject::InitBullet(BulletObject* p_bullet)
{
    if (p_bullet)
    {
        bool ret = p_bullet->LoadImg("img/player_bullet.png");

    }
}
