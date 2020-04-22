
/* LOP XU LY VU NO*/

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "BaseObject.h"
#include "GeneralFunction.h"

class Explosion : public BaseObject
{
public:
    Explosion();
    ~Explosion();

public:
    void setClip();
    void setFrame(const int& fr) {frame_ = fr;}
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width () const {return frame_width_;}
    int get_frame_height() const {return frame_height_;}

private:
    int frame_width_;
    int frame_height_;

    //Quan ly xem dang o frame thu bao nhieu
    unsigned int frame_;
    SDL_Rect frame_clip_[NUM_FRAME_EXPLOSION];
};

#endif // EXPLOSION_H
