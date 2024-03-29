
/*LOP XU LY NHAN VAT CHINH*/

#include "MainPlayer.h"
#include "Bullet.h"

MainPlayer::MainPlayer()
{
    x_pos_ = 0;
    y_pos_ = 0;

    x_val_ = 0;
    y_val_ = 0;

    come_back_time_ = 0;
    torch_count = 0;

    double_jump_ = false;
    won_ = false;

    frame_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;

    type_action_.left_ = 0;
    type_action_.right_ = 0;
    type_action_.down_ = 0;
    type_action_.up_ = 0;

    change_bullet_ = 0;
    change_dir_left_ = 0;
    change_dir_right_ = 0;

    on_ground_ = false;

    map_x_ = 0;
    map_y_ = 0;

    state_ = WALK_NONE;
}

MainPlayer::~MainPlayer()
{

}

bool MainPlayer::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool res = BaseObject::LoadImg(path, screen);

    if (res == true)
    {
        width_frame_ = rect_.w/8;
        height_frame_ = rect_.h;
    }
    return res;
}

SDL_Rect MainPlayer::GetFrameRect()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

void MainPlayer::SetClips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < NUM_FRAME_PLAYER; i++)
        {
            frame_clip_[i].x = width_frame_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void MainPlayer::ShowAnimation(SDL_Renderer* renderer)
{
    ControlPlayerImage(renderer);

    if (type_action_.left_ == 1 || type_action_.right_ == 1)
    {
        frame_++;
    }
    else
    {
        frame_ = 0;
    }

    if (frame_ >= NUM_FRAME_PLAYER)
    {
        frame_ = 0;
    }
    if (come_back_time_ == 0)
    {
        // tru di luong ban do bi cuon di
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* currentClip = &frame_clip_[frame_];

        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

        SDL_RenderCopy(renderer, object_, currentClip, &renderQuad);
    }
}

void MainPlayer::ImpInputAction(SDL_Event events, Mix_Chunk* bullet_sound[3], SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                state_ = WALK_RIGHT;
                type_action_.right_ = 1;
                type_action_.left_ = 0;
                ControlPlayerImage(screen);
            }
            break;
        case SDLK_LEFT:
            {
                state_ = WALK_LEFT;
                type_action_.left_ = 1;
                type_action_.right_ = 0;
                ControlPlayerImage(screen);
            }
            break;
        case SDLK_UP:
            {
                type_action_.jump_ = 1;
                double_jump_ = true;
            }
            break;
        case SDLK_c:
            {
                change_bullet_ ++;
                if (change_bullet_ > 2) change_bullet_ = 0;
            }
            break;
        case SDLK_z:
            {
                change_dir_left_ ++;
                if (change_dir_left_ > 3) change_dir_left_ = 0;
            }
            break;
        case SDLK_x:
            {
                change_dir_right_ ++;
                if (change_dir_right_ > 3) change_dir_right_ = 0;
            }
            break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                type_action_.right_ = 0;
            }
            break;
        case SDLK_LEFT:
            {
                type_action_.left_ = 0;
            }
            break;
        case SDLK_UP:
            {
                double_jump_ = false;
            }
            break;
        }
    }

    if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if (events.button.button == SDL_BUTTON_RIGHT)
        {
            type_action_.jump_ = 1;
        }
        else if (events.button.button == SDL_BUTTON_LEFT)
        {

            Bullet* pBullet = new Bullet();

            switch(change_bullet_)
            {
            case 0:
                pBullet->set_bullet_type(Bullet::GUN_BULLET);
                Mix_PlayChannel(-1, bullet_sound[0], 0);
                break;
            case 1:
                pBullet->set_bullet_type(Bullet::GRENADE_BULLET);
                Mix_PlayChannel(-1, bullet_sound[1], 0);
                break;
            case 2:
                pBullet->set_bullet_type(Bullet::MINE_BULLET);
                Mix_PlayChannel(-1, bullet_sound[2], 0);
                break;
            }

            pBullet->LoadImgBullet(screen);

            if (state_ == WALK_LEFT)
            {
                switch(change_dir_left_)
                {
                case 0:
                    pBullet->set_bullet_dir(Bullet::DIR_LEFT);
                    break;
                case 1:
                    pBullet->set_bullet_dir(Bullet::DIR_UP_LEFT);
                    break;
                case 2:
                    pBullet->set_bullet_dir(Bullet::DIR_DOWN_LEFT);
                    break;
                case 3:
                    pBullet->set_bullet_dir(Bullet::DIR_UP);
                    break;
                }
                // vi tri duong dau dan di ra
                pBullet->setRect(this->rect_.x, rect_.y+height_frame_*0.10);
            }
            else
            {
                switch(change_dir_right_)
                {
                case 0:
                    pBullet->set_bullet_dir(Bullet::DIR_RIGHT);
                    break;
                case 1:
                    pBullet->set_bullet_dir(Bullet::DIR_UP_RIGHT);
                    break;
                case 2:
                    pBullet->set_bullet_dir(Bullet::DIR_DOWN_RIGHT);
                    break;
                case 3:
                    pBullet->set_bullet_dir(Bullet::DIR_UP);
                    break;
                }
                pBullet->setRect(this->rect_.x+width_frame_-20, rect_.y+height_frame_*0.1);
            }

            pBullet->set_x_val(20);
            pBullet->set_y_val(20);
            pBullet->set_is_move(true);

            pBullet_list_.push_back(pBullet);
        }
    }
}

void MainPlayer::ImpBullet(SDL_Renderer* renderer)
{
    for (int i = 0; i < pBullet_list_.size(); i++)
    {
        Bullet* pBullet = pBullet_list_.at(i);
        if (pBullet != NULL)
        {
            if (pBullet->get_is_move() == true)
            {
                pBullet->ImpMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                pBullet->Render(renderer);
            }
            else
            {
                pBullet_list_.erase(pBullet_list_.begin()+i);
                if (pBullet != NULL)
                {
                    delete pBullet;
                    pBullet = NULL;
                }
            }
        }
    }
}

void MainPlayer::RemoveBullet(const int& x)
{
    int size = pBullet_list_.size();
    if (size > 0 && x < size)
    {
        Bullet* pBullet = pBullet_list_.at(x);
        pBullet_list_.erase(pBullet_list_.begin()+x);

        if (pBullet)
        {
            delete pBullet;
        }
    }
}

void MainPlayer::DoPlayer(Map& map_data)
{
    if (come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += FALL_VELOCITY;

        if (y_val_ >= FALL_VEL_MAX)
        {
            y_val_ = FALL_VEL_MAX;
        }

        if (type_action_.left_ == 1)
        {
            x_val_ -= PLAYER_VEL;
        }

        if (type_action_.right_ == 1)
        {
            x_val_ += PLAYER_VEL;
        }

        if (type_action_.jump_ == 1)
        {
            if (on_ground_ == true)
            {
                y_val_ = -JUMP_VEL;
            }
            if (!double_jump_) on_ground_ = false;
            type_action_.jump_ = 0;
        }

        CheckToMap(map_data);
        MakeCenter(map_data);
    }

    if (come_back_time_ > 0)
    {
        come_back_time_ --;
        // Reset lai vi tri
        if (come_back_time_ == 0)
        {
            on_ground_ = false;
            // Lui lai 4 o tile map
            if (x_pos_ > 4*TILE_SIZE)
            {
                x_pos_ -= 4*TILE_SIZE;
            }
            else
            {
                x_pos_ = 0;
            }
            y_pos_ = 0;
            x_val_ = 0;
            y_val_ = 0;
        }
    }
}

/* THAM KHAO VIDEO HUONG DAN CUA ANH PASS PHAM VA CO CHINH SUA THEM */
/* Trong do co thuat toan come_back_time khi vat roi xuong vuc va xu ly dan ban */

void MainPlayer::MakeCenter(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
    if (map_data.start_x_ < 0)
    {
        map_data.start_x_ = 0;
    }
    else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_-SCREEN_WIDTH;
    }

    map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/2);
    if (map_data.start_y_ < 0)
    {
        map_data.start_y_ = 0;
    }
    else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ = map_data.max_y_-SCREEN_HEIGHT;
    }
}


void MainPlayer::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Kiem tra theo chieu doc
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

    y1 = y_pos_/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
         //Nhan vat sang phai
        if (x_val_ > 0)
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if (val1 == TORCH_TILE || val2 == TORCH_TILE)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseTorch();
            }
            else
            {
                if (val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    // Dung tai vi tri do -> vi tri bien cua nhan vat
                    x_pos_ = x2*TILE_SIZE;
                    x_pos_ -= width_frame_ + 1;
                    x_val_ = 0;
                }
            }
            if (val1 == WINNER_TILE || val2 == WINNER_TILE)
            {
                won_ = true;
            }
        }
        else if (x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if (val1 == TORCH_TILE || val2 == TORCH_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                IncreaseTorch();
            }
            else
            {
                if (val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    x_pos_ = (x1+1)*TILE_SIZE;
                    x_val_ = 0;
                }
            }
            if (val1 == WINNER_TILE || val2 == WINNER_TILE)
            {
                won_ = true;
            }
        }
    }

    //Kiem tra theo chieu ngang

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

            if (val1 == TORCH_TILE || val2 == TORCH_TILE)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseTorch();
            }
            else
            {
                if (val1!= BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos_ = y2*TILE_SIZE;
                    y_pos_ -= height_frame_+1;
                    y_val_ = 0;
                    on_ground_ = true;
                    if (state_ == WALK_NONE)
                    {
                        state_ = WALK_RIGHT;
                    }
                }
            }
            if (val1 == WINNER_TILE || val2 == WINNER_TILE)
            {
                won_ = true;
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if (val1 == TORCH_TILE || val2 == TORCH_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseTorch();
            }
            else
            {
                if (val1 != BLANK_TILE || val2!= BLANK_TILE)
                {
                    y_pos_ = (y1+1)*TILE_SIZE;
                    y_val_ = 0;
                }
            }
            if (val1 == WINNER_TILE || val2 == WINNER_TILE)
            {
                won_ = true;
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
    //Kiem tra luc roi xuong vuc
    if (y_pos_ > map_data.max_y_)
    {
        come_back_time_ = 60;
    }
}

void MainPlayer::IncreaseTorch()
{
    torch_count++;
}

void MainPlayer::ControlPlayerImage(SDL_Renderer* renderer)
{
    if (on_ground_ == true)
    {
        if (state_ == WALK_LEFT)
        {
            LoadImg("assert/player_left_.png", renderer);
        }
        else
        {
            LoadImg("assert/player_right_.png", renderer);
        }
    }
    else
    {
        if (state_ == WALK_LEFT)
        {
            LoadImg("assert/jump_left.png", renderer);
        }
        else
        {
            LoadImg("assert/jump_right.png", renderer);
        }
    }
}

bool MainPlayer::GetRes()
{
    return won_;
}
