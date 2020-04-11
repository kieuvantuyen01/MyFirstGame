#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<windows.h>
#include<string>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

#include "TextObject.h"

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Audio
static Mix_Chunk* g_sound_bullet[3];
static Mix_Chunk* g_sound_explosion = NULL;
static Mix_Chunk* g_sound_ex_main = NULL;
static Mix_Music* g_sound = NULL;
static Mix_Chunk* g_end = NULL;

//Screen
const int FRAME_PER_SECOND = 25; //fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR =  0xff;

#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 4

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};
typedef struct Map // luu tru trang thai va vi tri cua cac o TileMap
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
    bool isInside(int& x,int& y,SDL_Rect object);
}
#endif // COMMON_FUNCTION_H_
