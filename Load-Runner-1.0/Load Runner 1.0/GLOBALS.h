//Header guards avoids double inclusion of the header file

#ifndef GLOBALS_H
#define GLOBALS_H

const int TILE_WIDTH = 54;
const int TILE_HEIGHT = 48;
const int ROWS = 13;
const int COLUMNS = 44;


enum TileObjs { FLOOR1, FLOOR2, LADDER ,NOTHING};
enum Keys { UP, DOWN, LEFT, RIGHT, SPACE, ESCAPE };
enum Acts { ACT_STARTMENU, ACT_GAME, ACT_GAMEOVER, ACT_GAMEWON,ACT_EXIT};

enum PlayerSpriteRow{FOR_RIGHT,FOR_LEFT,FOR_UP,FOR_FALL,FOR_DOWN = 2};
enum PlayerDirection {GOING_RIGHT,GOING_LEFT,GOING_UP,GOING_DOWN};
enum IDs {TREASURE,ENEMY};


//Returns the index in the array represented by passed row and col
inline int blockNumber(int row, int col)
{
	return COLUMNS*row + col;
}


//Window dimensions
const int WIDTH = 1188;
const int HEIGHT = 624;
//Frames per second
const int FPS = 60;

#endif


