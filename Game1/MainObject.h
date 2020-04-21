
/*LOP XU LY NHAN VAT CHINH*/

#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <vector>
#include "GeneralFunction.h"
#include "BaseObject.h"
#include "Bullet.h"

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void ShowAnimation(SDL_Renderer* renderer);
    void ImpInputAction(SDL_Event events, Mix_Chunk* bullet_sound[3],
                           SDL_Renderer* screen);
    void SetClips();

    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void SetPlayerMap(const int map_x, const int map_y){map_x_ = map_x; map_y_ = map_y;}
    void MakeCenter(Map& map_data);
    void ControlPlayerImage(SDL_Renderer* renderer);
    SDL_Rect GetFrameRect();

    void SetBulletList(std::vector<Bullet*>bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }
    std::vector<Bullet*> get_bullet_list() const {return p_bullet_list_;}
    void ImpBullet(SDL_Renderer* renderer);
    void RemoveBullet(const int& x);
    void IncreaseTorch();

    void SetComeBackTime (const int& cb_time) {come_back_time_ = cb_time;}
    int GetTorchCount() const {return torch_count;}
    bool GetRes();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };

private:

    int torch_count;
    std::vector<Bullet*> p_bullet_list_;
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    int change_bullet_;
    int change_dir_left_;
    int change_dir_right_;
    bool double_jump_;

    SDL_Rect frame_clip_[NUM_FRAME_PLAYER];
    Input type_action_;
    int frame_;
    int status_;
    bool on_ground_;

    bool won_;

    int map_x_;
    int map_y_;

    int come_back_time_;
};
#endif // MAIN_OBJECT_H
