
#ifndef PLANE_OBJECT_H_
#define PLANE_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define WIDHT_PLANE 80
#define HEIGHT_PLANE 33

class PlaneObject : public BaseObject
{
public:
    PlaneObject();
    ~PlaneObject();

    void HandleMove(const int& x_border, const int& y_border);
    void HandleInput(SDL_Event events);

    void set_x_val(const int& val) {x_val_ = val;}
    void set_y_val(const int& val) {y_val_ = val;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void SetBulletList(std::vector<BulletObject*> bullet_list) {p_bullet_list_ = bullet_list;}
    std::vector<BulletObject*> GetBulletList() const {return p_bullet_list_;}

    void InitBullet(BulletObject* p_object_);
    void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit);
    void Reset(const int& xborder);
    void ResetBullet(BulletObject* p_bullet);

private:
    int x_val_;
    int y_val_;

    std::vector<BulletObject*> p_bullet_list_;

};
#endif // PLANE_OBJECT_H_
