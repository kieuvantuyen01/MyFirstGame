
/*LOP XU LY ENEMIES*/

#include "Enemy.h"

EnemiesObiect::EnemiesObiect()
{
    x_vel_ = 0;
    y_vel_ = 0;
    x_pos_ = 0.0;
    y_pos_ = 0.0;
    width_frame_ = 0;
    height_frame_ = 0;
    frame_ = 0;
    on_ground_ = 0;
    come_back_time_ = 0;

    animation_a_ = 0;
    animation_b_ = 0;
    input_type_.left_ = 0;
    type_move_ = STATIC_ENEMY;
}

EnemiesObiect::~EnemiesObiect()
{

}

SDL_Rect EnemiesObiect::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

bool EnemiesObiect::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret)
    {
        width_frame_ = rect_.w/ENEMY_FRAME_NUM;
        height_frame_ = rect_.h;
    }
    return ret;
}

void EnemiesObiect::SetClips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < ENEMY_FRAME_NUM; i++)
        {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void EnemiesObiect::Show(SDL_Renderer* des)
{
    if (come_back_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= ENEMY_FRAME_NUM)
        {
            frame_ = 0;
        }
        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy(des, object_, currentClip, &renderQuad);
    }
}

void EnemiesObiect::DoEnemy(Map& gMap)
{
    if (come_back_time_ == 0)
    {
        x_vel_ = 0;
        y_vel_ += FALL_VELOCITY;
        if (y_vel_ >= FALL_VEL_MAX)
        {
            y_vel_ = FALL_VEL_MAX;
        }

        if (input_type_.left_ == 1)
        {
            x_vel_ -= ENEMY_VEL;
        }
        else if (input_type_.right_ == 1)
        {
            x_vel_ += ENEMY_VEL;
        }

        CheckToMap(gMap);
    }
    else if (come_back_time_ > 0)
    {
        come_back_time_ --;
        if (come_back_time_ == 0)
        {
            InitEnemies();
        }
    }
}

void EnemiesObiect::InitEnemies()
{
    x_vel_ = 0;
    y_vel_ = 0;
    if (x_pos_ > 256)
    {
        x_pos_ -= 256;
        animation_a_ -= 256;
        animation_b_ -= 256;
    }
    else
    {
        x_pos_ = 0;
    }
    y_pos_ = 0;
    come_back_time_ = 0;
    input_type_.left_ = 1;
}

void EnemiesObiect::RemoveBullet(const int& idx)
{
    int size = bullet_list_.size();
    if (size > 0 && idx < size)
    {
        Bullet* p_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin()+idx);

        if (p_bullet)
        {
            delete p_bullet;
        }
    }
}

/* THAM KHAO VIDEO HUONG DAN CUA ANH PASS PHAM VA CO CHINH SUA THEM */
/* Hoan toan tuong tu nhu voi MainObject*/

void EnemiesObiect::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Check for hozirontal
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_vel_)/TILE_SIZE;
    x2 = (x_pos_ + x_vel_ + width_frame_ - 1)/TILE_SIZE;

    y1 = y_pos_/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_vel_ > 0) //main object is moving to right
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if ((val1 != BLANK_TILE && val1 != TORCH_TILE) || (val2 != BLANK_TILE && val2 != TORCH_TILE))
            {
                x_pos_ = x2*TILE_SIZE; // Dung tai vi tri do -> vi tri bien cua nhan vat
                x_pos_ -= width_frame_ + 1;
                x_vel_ = 0;
            }
        }
        else if (x_vel_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if ((val1 != BLANK_TILE && val1 != TORCH_TILE) || (val2 != BLANK_TILE && val2 != TORCH_TILE))
            {
                x_pos_ = (x1+1)*TILE_SIZE;
                x_vel_ = 0;
            }
        }
    }

    //check vertical

    int width_min  = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_+width_min)/TILE_SIZE;

    y1 = (y_pos_+y_vel_)/TILE_SIZE;
    y2 = (y_pos_+y_vel_+height_frame_-1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_vel_ > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if ((val1!= BLANK_TILE && val1 != TORCH_TILE) || (val2 != BLANK_TILE && val2 != TORCH_TILE))
            {
                y_pos_ = y2*TILE_SIZE;
                y_pos_ -= height_frame_+1;
                y_vel_ = 0;
                if (!is_fly_)
                {
                    on_ground_ = true;
                }
            }
        }
        else if (y_vel_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if ((val1 != BLANK_TILE && val1 != TORCH_TILE) || (val2!= BLANK_TILE && val2 != TORCH_TILE))
            {
                y_pos_ = (y1+1)*TILE_SIZE;
                y_vel_ = 0;
            }
        }
    }

    x_pos_ += x_vel_;
    if (is_fly_) y_vel_ = 0;
    y_pos_ += y_vel_;

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_-width_frame_-1;
    }
    if (y_pos_ > map_data.max_y_) // kiem tra luc roi xuong vuc tham
    {
        come_back_time_ = 60;
    }
}

void EnemiesObiect::ImpMoveType(SDL_Renderer* screen)
{
    if (type_move_ == STATIC_ENEMY)
    {
        //
    }
    else if (type_move_ == MOVE_IN_SPACE_ENEMY)
    {
        if (on_ground_ == true)
        {
            if (x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadImg("assert/enemy_left.png", screen);
            }
            else if (x_pos_ < animation_a_)
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;
                LoadImg("assert/enemy_right.png", screen);
            }
        }
        else
        {
            if (input_type_.left_ == 1)
            {
                LoadImg("assert/enemy_left.png", screen);
            }
        }
    }
    else
    {
        is_fly_ = true;
        on_ground_ = false;
        if (input_type_.left_ == 1)
        {
            LoadImg("assert/plane_left.png", screen);
        }
    }

}

void EnemiesObiect::InitBullet(Bullet* p_bullet, SDL_Renderer* screen)
{
    if (p_bullet != NULL)
    {
        if (type_move_ == STATIC_ENEMY)
        {
            p_bullet->set_bullet_type(Bullet::TANK_BULLET);
            p_bullet->set_bullet_dir(Bullet::DIR_LEFT);
        }
        else if (type_move_ == FLY_ENEMY)
        {
            p_bullet->set_bullet_type(Bullet::BOMB_BULLET);
            p_bullet->set_bullet_dir(Bullet::DIR_DOWN_LEFT);
        }

        bool ret = p_bullet->LoadImgBullet(screen);
        if (!ret)
        {
            return;
        }
        p_bullet->setRect(rect_.x-30, y_pos_+65); // hien thi tren man hinh kich thuoc 1280
        p_bullet->set_x_val(20);//set toc do
        p_bullet->set_is_move(true);
        bullet_list_.push_back(p_bullet);
    }
}

void EnemiesObiect::GenerateBullet(SDL_Renderer* screen, const int& x_litmit, const int& y_limit)
{
    for (int i = 0; i < bullet_list_.size(); i++)
    {
        Bullet* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                // Kiem soat de dan duoc ban trong pham vi 0->300;
                int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x;
                if (bullet_distance < BULLET_DISTANCE_MAX && bullet_distance > 0)
                {
                    p_bullet->ImpMove(x_litmit, y_limit);
                    p_bullet->Render(screen);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }
            }
            else // gan lai trang thai ban dau khi dan di het gioi han man hinh
            {
                p_bullet->set_is_move(true);
                p_bullet->setRect(rect_.x-30, y_pos_+65);
            }
        }
    }
}
