#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<windows.h>
#include<string>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<fstream>

//Global Var
static TTF_Font* gFont = NULL;
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

//Audio
static Mix_Chunk* gSound_bullet[3];
static Mix_Chunk* gSound_explosion = NULL;
static Mix_Chunk* gSound_ex_main = NULL;
static Mix_Music* gSound_start = NULL;
static Mix_Music* gSound_end = NULL;

//Screen
const int FRAME_PER_SECOND = 25; //fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

//
const int NUM_DIE = 3;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR =  0xff;

#define BLANK_TILE 0
#define STATE_TORCH 4

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define MAX_TIME_GAME 304
#define MAX_ENEMIES_GAME 60

struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};
struct Map // luu tru trang thai va vi tri cua cac o TileMap
{
    // vi tri cua o Tile Mat
    int start_x_;
    int start_y_;
    // chi so cua o Tile Mat
    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    bool isInside(int& x, int& y, SDL_Rect object);
    int MakeRandValue(const int& val_ = 400);
    void waitUntilKeyPressed();
}
#endif // COMMON_FUNCTION_H_
