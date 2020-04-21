
/* LOP XU LY VU NO*/

#include "Explosion.h"

Explosion::Explosion()
{
    frame_ = 0;
    frame_width_ = 0;
    frame_height_ = 0;
}

Explosion::~Explosion()
{

}

bool Explosion::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret)
    {
        frame_width_ = rect_.w/NUM_FRAME_EXPLOSION;
        frame_height_ = rect_.h;
    }

    return ret;
}

void Explosion::set_clip()
{
    if (frame_width_ > 0 && frame_height_ > 0)
    {
        for (int i = 0; i < NUM_FRAME_EXPLOSION; i++)
        {
            frame_clip_[i].x = frame_width_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = frame_width_;
            frame_clip_[i].h = frame_height_;
        }
    }
}

void Explosion::Show(SDL_Renderer* screen)
{
    SDL_Rect* currentClip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, frame_width_, frame_height_};
    if (currentClip != NULL)
    {
        renderQuad.w = currentClip->w;
        renderQuad.h = currentClip->h;
    }

    SDL_RenderCopy(screen, object_, currentClip, &renderQuad);
}
