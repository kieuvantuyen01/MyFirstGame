#include "ThreatsObject.h"

ThreatsObiect::ThreatsObiect()
{
    x_val_ = 0;
    y_val_ = 0;
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
    type_move_ = STATIC_THREAT;
}

ThreatsObiect::~ThreatsObiect()
{

}

SDL_Rect ThreatsObiect::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

bool ThreatsObiect::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret)
    {
        width_frame_ = rect_.w/THREAT_FRAME_NUM;
        height_frame_ = rect_.h;
    }
    return ret;
}

void ThreatsObiect::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < THREAT_FRAME_NUM; i++)
        {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void ThreatsObiect::Show(SDL_Renderer* des)
{
    if (come_back_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= THREAT_FRAME_NUM)
        {
            frame_ = 0;
        }
        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect rendQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
    }
}

void ThreatsObiect::DoPlayer(Map& gMap)
{
    if (come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += THREAT_GRAVITY_SPEED;
        if (y_val_ >= THREAD_MAX_FALL_SPEED)
        {
            y_val_ = THREAD_MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if (input_type_.right_ == 1)
        {
            x_val_ += THREAT_SPEED;
        }

        CheckToMap(gMap);
    }
    else if (come_back_time_ > 0)
    {
        come_back_time_ --;
        if (come_back_time_ == 0)
        {
            InitThreats();
        }
    }
}

void ThreatsObiect::InitThreats()
{
    x_val_ = 0;
    y_val_ = 0;
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

void ThreatsObiect::RemoveBullet(const int& idx)
{
    int size = bullet_list_.size();
    if (size > 0 && idx < size)
    {
        BulletObject* p_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin()+idx);

        if (p_bullet)
        {
            delete p_bullet;
        }
    }
}

void ThreatsObiect::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Check for hozirontal
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

    y1 = y_pos_/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) //main object is moving to right
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if ((val1 != BLANK_TILE && val1 != STATE_TORCH) || (val2 != BLANK_TILE && val2 != STATE_TORCH))
            {
                x_pos_ = x2*TILE_SIZE; // Dung tai vi tri do -> vi tri bien cua nhan vat
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if (x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if ((val1 != BLANK_TILE && val1 != STATE_TORCH) || (val2 != BLANK_TILE && val2 != STATE_TORCH))
            {
                x_pos_ = (x1+1)*TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    //check vertical

    int width_min  = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_+width_min)/TILE_SIZE;

    y1 = (y_pos_+y_val_)/TILE_SIZE;
    y2 = (y_pos_+y_val_+height_frame_-1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if ((val1!= BLANK_TILE && val1 != STATE_TORCH) || (val2 != BLANK_TILE && val2 != STATE_TORCH))
            {
                y_pos_ = y2*TILE_SIZE;
                y_pos_ -= height_frame_+1;
                y_val_ = 0;
                on_ground_ = true;
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if ((val1 != BLANK_TILE && val1 != STATE_TORCH) || (val2!= BLANK_TILE && val2 != STATE_TORCH))
            {
                y_pos_ = (y1+1)*TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;
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

void ThreatsObiect::ImpMoveType(SDL_Renderer* screen)
{
    if (type_move_ == STATIC_THREAT)
    {
        //
    }
    else
    {
        if (on_ground_ == true)
        {
            if (x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadImg("img/threat_left.png", screen);
            }
            else if (x_pos_ < animation_a_)
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;
                LoadImg("img/threat_right.png", screen);
            }
        }
        else
        {
            if (input_type_.left_ == 1)
            {
                LoadImg("img/threat_left.png", screen);
            }
        }
    }
}

void ThreatsObiect::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if (p_bullet != NULL)
    {
        p_bullet->set_bullet_type(BulletObject::TANK_BULLET);
        bool ret = p_bullet->LoadImgBullet(screen);

        if (ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->setRect(rect_.x-30, y_pos_+65); // hien thi tren man hinh kich thuoc 1280
            p_bullet->set_x_val(20);//set toc do
            bullet_list_.push_back(p_bullet);
        }
    }
}

void ThreatsObiect::MakeBullet(SDL_Renderer* screen, const int& x_litmit, const int& y_limit)
{
    for (int i = 0; i < bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x; // kiem soat de dan duoc ban trong pham vi 0->300;
                if (bullet_distance < 400 && bullet_distance > 0)
                {
                    p_bullet->HandleMove(x_litmit, y_limit);
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
