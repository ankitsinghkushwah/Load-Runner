
#ifndef ENEMY_H
#define ENEMY_H

//STD C++ HEADERS
#include<vector>

//USER DEFINED HEADERS
#include"Map.h"
#include"Player.h"
#include"GameObject.h"
#include"GLOBALS.h"


class Enemy :public GameObject
{
	std::vector<int> path;

	ALLEGRO_BITMAP *enemySprite;

	PlayerSpriteRow spriteCurrRow;
	Player *player;
	int map[ROWS*COLUMNS];

	int x;
	int y;
	int width;
	int height;
	
	int row;
	int col;
	int indexRow;
	int indexCol;
	int speed;
	
	int sourceX;
	int frameDelay;
	int currFrame;
	
	int AIMap[ROWS*COLUMNS];
	bool checkRow;
	bool checkCol;
	
	int count;
	int xOffSet;
	int yOffSet;

	int pathLastRow;
	int pathLastCol;

public:

	Enemy() {}
	Enemy(ALLEGRO_BITMAP *enemySprite,int map[],Player *player, int curRow, int curCol,PlayerSpriteRow spriteCurrRow);
	~Enemy();
	bool collided(GameObject *player);
	int getID();
	void update();
	void render();
};
#endif
