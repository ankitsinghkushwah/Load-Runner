#include"Map.h"
using namespace std;



Map::Map(ALLEGRO_BITMAP *lTiles,int map[])
{
	this->tiles = lTiles;
	for (int i = 0; i < ROWS*COLUMNS; i++)
		this->map[i] = map[i];
}


Map::~Map() {}

void Map::render()
{
	for (int i = 0; i < ROWS*COLUMNS; i++)
	{
		if(map[i]!=3)
		al_draw_bitmap_region(tiles,map[i]*TILE_WIDTH,0,TILE_WIDTH,TILE_HEIGHT,TILE_WIDTH*(i%COLUMNS),TILE_HEIGHT*(i/COLUMNS),0);
	}
}



