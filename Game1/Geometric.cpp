
/*LOP XU LY KHU VUC HIEN THI DATA GAME*/

#include "Geometric.h"

void Geometric::RenderRectangle(const RectFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen)
{
    SDL_Rect fill_rect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_};
    SDL_SetRenderDrawColor(screen, color_data.red_, color_data.green_, color_data.blue_, 0xFF);
    SDL_RenderFillRect(screen, &fill_rect);
}

void Geometric::RenderOutline(const RectFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen)
{
    SDL_Rect out_rect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_};
    SDL_SetRenderDrawColor(screen, color_data.red_, color_data.green_, color_data.blue_, 0xFF);
    SDL_RenderDrawRect(screen, &out_rect);
}

/*THAM KHAO CACH DUNG BIEN LUU DU LIEU DE HIEN THI THONG SO GAME TU ANH PASS PHAM*/
