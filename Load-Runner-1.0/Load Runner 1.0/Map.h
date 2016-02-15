//Header guards avoids double inclusion of the header file
#ifndef MAP_H
#define MAP_H

#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>

#include"GameObject.h"
#include"GLOBALS.h"


class Map : public GameObject
{
	ALLEGRO_BITMAP *tiles;

	int map[ROWS*COLUMNS];

public:

	Map(ALLEGRO_BITMAP *tilesImage,int map[]);
	~Map();
	void render();
};


#endif