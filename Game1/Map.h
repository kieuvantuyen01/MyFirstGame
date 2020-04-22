
/* LOP XU LY BAN DO GAME*/

#ifndef MAP_H
#define MAP_H

#include "GeneralFunction.h"
#include "BaseObject.h"

class Tile: public BaseObject
{
public:
    Tile();
    ~Tile();
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char * name);
    void SetTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const{return game_map_;}
    void SetMap(Map& map_data) {game_map_ = map_data;}
private:
    Map game_map_;
    Tile tile_map_[MAX_TILES];
};
#endif // MAP_H
