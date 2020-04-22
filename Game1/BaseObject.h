
/* LOP CO SO DE LOAD ANH */

#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "GeneralFunction.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    void setRect(const int x, const int y) {rect_.x = x, rect_.y = y;}
    SDL_Rect GetRect() const {return rect_;}

    void SetObject(SDL_Texture* object) {object_ = object;}
    SDL_Texture* GetObject() const {return object_;}

    void SetWidthHeight(const int& w,const int& h) {rect_.w = w; rect_.h = h;}
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Clean();

protected:
    SDL_Texture* object_;
    SDL_Rect rect_;

};
#endif // BASE_OBJECT_H
