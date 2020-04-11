#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void setRect(const int x, const int y) {rect_.x = x, rect_.y = y;}
    SDL_Rect GetRect() const {return rect_;}
    void SetObject(SDL_Texture* object) {p_object_=object;}
    SDL_Texture* GetObject() const {return p_object_;}

    void SetWidHei(const int& w,const int& h) {rect_.w=w;rect_.h=h;}
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();

protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;

};
#endif // BASE_OBJECT_H_
