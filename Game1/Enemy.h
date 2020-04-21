
/*LOP XU LY ENEMIES*/

#ifndef ENEMY_H
#define ENEMY_H

#include "GeneralFunction.h"
#include "BaseObject.h"
#include "Bullet.h"

class EnemiesObiect : public BaseObject
{
public:
    EnemiesObiect();
    ~EnemiesObiect();

    void set_x_val(const float xVal) {x_vel_ = xVal;}
    void set_y_val(const float yVal) {y_vel_ = yVal;}

    void set_x_pos(const float xp) {x_pos_ = xp;}
    void set_y_pos(const float yp) {y_pos_ = yp;}

    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}

    void SetMapXY(const int mp_x, const int mp_y) {map_x_ = mp_x; map_y_ = mp_y;}

    void SetClips();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer *des);
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
    void DoEnemy(Map& gMap);
    void CheckToMap(Map& gMap);

    void InitEnemies();
    void set_type_move(const int& typeMove) {type_move_ = typeMove;}
    void SetAnimationPos(const int& pos_a, const int& pos_b) {animation_a_ = pos_a; animation_b_ = pos_b;}
    void set_input_left(const int& ipLeft) {input_type_.left_ = ipLeft;}
    void ImpMoveType(SDL_Renderer* screen); // ham xu ly cac van de di chuyen
    SDL_Rect GetRectFrame();

    std::vector<Bullet*> get_bullet_list() const {return bullet_list_;}
    void SetBulletList(const std::vector<Bullet*>& bl_list) {bullet_list_ = bl_list;}

    void InitBullet(Bullet* p_bullet, SDL_Renderer* screen);
    void GenerateBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& idx);

    enum TypeMove
    {
        STATIC_ENEMY = 0,
        MOVE_IN_SPACE_ENEMY = 1,
        FLY_ENEMY = 2,
    };

private:

    int map_x_;
    int map_y_;

    float x_vel_;
    float y_vel_;
    float x_pos_;
    float y_pos_;
    bool on_ground_;
    bool is_fly_;

    int come_back_time_;
    SDL_Rect frame_clip_[ENEMY_FRAME_NUM];

    int width_frame_;
    int height_frame_;
    int frame_;

    int type_move_;
    int animation_a_;
    int animation_b_;
    Input input_type_;

    std::vector<Bullet*> bullet_list_;
};
#endif // ENEMY_H
