
/*LOP XU LY KHU VUC HIEN THI DATA GAME*/

#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "GeneralFunction.h"

struct RectFormat
{
    int left_;
    int top_;
    int width_;
    int height_;

    RectFormat(int left, int top, int width, int height)
    {
        left_ = left;
        top_ = top;
        width_ = width;
        height_ = height;
    }
};

struct ColorData
{
    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;

    ColorData(Uint8 r, Uint8 g, Uint8 b)
    {
        red_ = r;
        green_ = g;
        blue_ = b;
    }
};

class Geometric
{
public:
    static void RenderRectangle(const RectFormat& rect_size, const ColorData& color_data, SDL_Renderer* screen);
    static void RenderOutline(const RectFormat& rect_size, const ColorData& color_data, SDL_Renderer* screen);
};

#endif // GEOMETRIC_H
