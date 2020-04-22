
/* LOP XU LY CAC HAM CHUNG */

#ifndef GENERAL_FUNCTION_H
#define GENERAL_FUNCTION_H

#include<windows.h>
#include<string>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<fstream>

//Khai bao bien toan cuc
static TTF_Font* gFont = NULL;
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

//Am thanh
static Mix_Chunk* gSound_bullet[3];
static Mix_Chunk* gSound_explosion = NULL;
static Mix_Chunk* gSound_ex_main = NULL;
static Mix_Music* gSound_start = NULL;
static Mix_Music* gSound_end = NULL;

//Kich thuoc man hinh
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

//FPS
const int FRAME_PER_SECOND = 25;
const int real_frame_time_ = 1000/FRAME_PER_SECOND;

const int NUM_DIE = 3;

// Color Key
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR =  0xff;

#define BLANK_TILE 0
#define TORCH_TILE 4
#define WINNER_TILE 19

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define MAX_TILES 20
#define MAX_TIME_GAME 304
#define MAX_ENEMIES_GAME 60

//Toc do nhan vat chinh
#define FALL_VELOCITY 0.8
#define FALL_VEL_MAX 10
#define PLAYER_VEL 8
#define JUMP_VEL 18
#define NUM_FRAME_PLAYER 8

//Toc do cua Enemies
#define ENEMY_FRAME_NUM 8
#define ENEMY_VEL 3

#define BULLET_DISTANCE_MAX 400

#define NUM_FRAME_EXPLOSION 8

//Cac bien luu giu trang thai ban dau
struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

//Luu tru trang thai va vi tri cua cac o TileMap
struct Map
{
    // Vi tri bat dau cua ban do (di chuyen theo nhan vat)
    int start_x_;
    int start_y_;

    // Vi tri toi da cua ban do
    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
    bool isInside(int& x, int& y, SDL_Rect object);
    int MakeRandValue(const int& val_ = 400);
    void waitUntilKeyPressed();
}

#endif // GENERAL_FUNCTION_H
