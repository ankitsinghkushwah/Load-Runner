//Header guards avoids double inclusion of the header file


#ifndef TREASURE_H
#define TREASURE_H

#include"GameObject.h"
#include "GLOBALS.h"
#include<allegro5/allegro.h>
#include"Player.h"

class Treasure:public GameObject
{
	int x1;
	int y1;
	int x2;
	int y2;
	ALLEGRO_BITMAP *image;

public:

	Treasure() {}

	Treasure(int row, int col, ALLEGRO_BITMAP *image)
	{
		this->image = image;
 
		x1 = col*TILE_WIDTH;
		x2 = x1 + TILE_WIDTH;
		y1 = row*TILE_HEIGHT;
		y2 = y1 + TILE_HEIGHT;
	}
	
	bool collided(GameObject* player)
	{
		
		if (player->getDir() == FOR_RIGHT)
		{
			if (player->getX() + TILE_WIDTH > x1 && player->getX() + TILE_WIDTH<x2 && player->getY() + 2 > y1 && player->getY() + 2 < y2)
			{
				return true;
			}
		}
		else if (player->getDir() == FOR_LEFT)
		{
			if (player->getX() > x1 && player->getX() < x2 && player->getY()+2 > y1 && player->getY()+2 < y2)
			{
				return true;
			}
		}
		
		return false;
	}

	
	int getID() { return TREASURE; }
	
	
	void render()
	{
		al_draw_bitmap(image,x1,y1,0);
	}

};

#endif