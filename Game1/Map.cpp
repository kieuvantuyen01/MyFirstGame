
/* LOP XU LY BAN DO GAME*/

#include "Map.h"
#include "GeneralFunction.h"

Tile::Tile()
{

}

Tile::~Tile()
{

}

/*THAM KHAO TREN LAZYFOO + PHATTRIENPHANMEM123AZ VA CO BO SUNG */
void GameMap::LoadMap(char* name)
{
    std::ifstream input(name);
    if (!input)
    {
        return;
    }

    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
           input >> game_map_.tile[i][j];
           int val = game_map_.tile[i][j];
           if (val > 0)
           {
               // Lay vi tri
               if (j > game_map_.max_x_)
               {
                   game_map_.max_x_ = j;
               }
               if (i > game_map_.max_y_)
               {
                   game_map_.max_y_ = i;
               }
           }
        }
    }

    // vi tri toi da cua ban do
    game_map_.max_x_ = (game_map_.max_x_+1)*TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_+1)*TILE_SIZE;

    // vi tri bat dau cua ban do
    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    input.close();
}

void GameMap::SetTiles(SDL_Renderer* screen)
{
    std::string file_name = "";

    for (int i = 0; i < MAX_TILES; i++)
    {
        file_name = "map/" + std::to_string(i) + ".png" ;

        std::ifstream input(file_name);
        if (!input)
        {
            continue;
        }

        input.close();

        tile_map_[i].LoadImg(file_name, screen);
    }
}

/* THAM KHAO VIDEO HUONG DAN CUA ANH PASS PHAM VE CACH FILL ANH */
// fill cac hinh anh vao o Tile map
void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    // xac dinh xem dang o o thu bao nhieu de fill
    map_x = game_map_.start_x_/TILE_SIZE;
    x1 = (game_map_.start_x_%TILE_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map_.start_y_/TILE_SIZE;
    y1 = (game_map_.start_y_%TILE_SIZE)*-1;
    y2 = x1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x_/TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x];
            if (val > 0)
            {
                tile_map_[val].setRect(j, i);
                tile_map_[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
