//Header guards avoids double inclusion of the header file

#ifndef PLAYER_H
#define PLAYER_H

#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>

#include"GameObject.h"
#include"Map.h"
#include"GLOBALS.h"


class Player : public GameObject
{
protected:

	ALLEGRO_BITMAP *playerSprite;
	
	PlayerSpriteRow spriteCurrRow;
	
	bool onLadder;
	bool falling;
	bool canGo[4];
	bool colliding;
	
	int sourceX;
	int frameDelay;
	int currFrame;
	int x;
	int y;
	int width;
	int height;
	int speed;
	
	int x1Lim;
	int x2Lim;
	int y1Lim;
	int y2Lim;

	int xOffSet;
	int yOffSet;

	int map[ROWS*COLUMNS];

	int lastVertDir;

	int direction;


public:
	Player();
	Player(ALLEGRO_BITMAP *playerSprite,int map[] ,int curRow,int curCol) ;
	~Player();
	
	bool collidingWithGround(int x, int &y);
	bool currPosHasLadder(int x, int y, int &row, int &col);
	bool wallIsAhead(int x,int y);
	int getBottomLimOfLadder(int row, int col);
	int getTopLimOfLadder(int row,int col);

	int getDir() { return direction; }
	int getX() { return x; }
	int getY() { return y; }
	int getRow();
	int getCol();


	void onKeyLeft();
	void onKeyRight();
	void onKeyUp();
	void onKeyDown();
	void onKeyReleased();
	void update();
	void render();
};


#endif
