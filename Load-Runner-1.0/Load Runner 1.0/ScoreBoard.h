//Header guards avoids double inclusion of the header file

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include"GameObject.h"
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_font.h>
#include"GLOBALS.h"

class ScoreBoard : public GameObject
{
	int x;
	int y;
	int width;
	int height;
	int treasuresTaken;
	int totalTreasures;
	ALLEGRO_FONT *font;
	
public:

	ScoreBoard() {}
	
	ScoreBoard(ALLEGRO_FONT *font,int totalTreasures) 
	{
		this->totalTreasures = totalTreasures;
		treasuresTaken = 0;
		this->font = font;
		x = y = 0;
		width = WIDTH;
		height = HEIGHT;
	}

	void plusTreasure()
	{
		treasuresTaken++;
	}

	int getTreasures(){return treasuresTaken;}

	void updatePos(int playerX,int playerY)
	{
		if(playerX+TILE_WIDTH/2 > WIDTH/2)
			x += playerX - WIDTH/2;
	}
	
	void render()
	{
		al_draw_filled_rectangle(x,y,width,50,al_map_rgb(176,176,0));
		al_draw_textf(font,al_map_rgb(0,0,0),10,5,0,"REMAINING TREASURE %i",(totalTreasures-treasuresTaken));
	}
};

#endif
