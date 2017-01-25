
#include"Enemy.h"
#include"Dijkstra.h"


Enemy::Enemy(ALLEGRO_BITMAP *enemySprite, int map[],Player*player, int curRow, int curCol,PlayerSpriteRow spriteCurrRow)
{

	//copying original map to Player::map
	for (int i = 0; i < ROWS*COLUMNS; i++)
	{
		this->map[i] = map[i];
	}

	//Generating A different map for for dijkstra algorithm
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			if (map[blockNumber(row + 1, col)] == FLOOR1 || map[blockNumber(row + 1, col)] == FLOOR2 || map[blockNumber(row, col)] == LADDER|| map[blockNumber(row+1, col)] == LADDER)
				AIMap[blockNumber(row, col)] = 1;
			else
				AIMap[blockNumber(row, col)] = 10;
		}
	}

	//setting player up

	this->spriteCurrRow = spriteCurrRow;

	this->row = curRow;
	this->col = curCol;

	x = col * TILE_WIDTH;
	y = row * TILE_HEIGHT;

	indexRow = 0;
	indexCol = 0;

	width = TILE_WIDTH;
	height = TILE_HEIGHT;

	sourceX = 0;

	this->enemySprite = enemySprite;

	this->frameDelay = 8;
	this->currFrame = 0;
	
	this->player = player;

	checkRow = checkCol = true;

	xOffSet = 19;
	yOffSet = 2;
	
	count = 1;

	

	int playerRow = player->getRow();
	int playerCol = player->getCol();


	path = dijsktra(AIMap, new Node(AIMap[blockNumber(row, col)], row, col, 0), new Node(AIMap[blockNumber(playerRow, playerCol)], playerRow, playerCol, 0));
	
	pathLastCol = path[path.size() - 1] % COLUMNS;
	pathLastRow = path[path.size() - 1] / COLUMNS;

	speed = 4;
}


Enemy::~Enemy() {}


void Enemy::update()
{
	

	int playerRow = player->getRow();
	int playerCol = player->getCol();
	

	if (checkRow)
	{
		if (row == playerRow)
		{
			path = dijsktra(AIMap,new Node(AIMap[blockNumber(row, col)], row, col, 0),new Node(AIMap[blockNumber(playerRow,playerCol)],playerRow,playerCol,0));
			count = 1;
			pathLastCol = path[path.size() - 1] % COLUMNS;
			pathLastRow = path[path.size() - 1] / COLUMNS;

			checkRow = false;
			checkCol = true;
		}
	}

	if (checkCol)
	{
		if (col == playerCol)
		{
			path = dijsktra(AIMap, new Node(AIMap[blockNumber(row, col)], row, col, 0), new Node(AIMap[blockNumber(playerRow, playerCol)], playerRow, playerCol, 0));
			count = 1;
			pathLastCol = path[path.size() - 1] % COLUMNS;
			pathLastRow = path[path.size() - 1] / COLUMNS;

			checkCol = false;
			checkRow = true;
		}
	}


	
	if (row == pathLastRow && col == pathLastCol)
	{
		path = dijsktra(AIMap, new Node(AIMap[blockNumber(row, col)], row, col, 0), new Node(AIMap[blockNumber(playerRow, playerCol)], playerRow, playerCol, 0));
		count = 1;
		pathLastCol = path[path.size() - 1] % COLUMNS;
		pathLastRow = path[path.size() - 1] / COLUMNS;
	}

	indexCol = path[count] % COLUMNS;
	indexRow = path[count] / COLUMNS;


	if (row < indexRow)
	{
		spriteCurrRow = FOR_DOWN;
		y += speed;
		if (y+yOffSet > indexRow * TILE_HEIGHT)
		{
			row = indexRow;
			count++;
		}

		if (++currFrame >= frameDelay)
		{
			if (++sourceX > 2)
				sourceX = 1;
			currFrame = 0;
		}
	
	}

	if (row > indexRow)
	{
		spriteCurrRow = FOR_UP;
		y -= speed;
		if ((y+height-yOffSet) < (indexRow+1) * TILE_HEIGHT)
		{
			row = indexRow;
			count++;
		}

		if (++currFrame >= frameDelay)
		{
			if (++sourceX > 2)
				sourceX = 1;
			currFrame = 0;
		}
		
	}


	if (col < indexCol)
	{
		spriteCurrRow = FOR_RIGHT;
		x += speed;
		if (x+xOffSet > indexCol * TILE_WIDTH)
		{
			col = indexCol;
			count++;
		}

		if (++currFrame >= frameDelay)
		{
			if (++sourceX > 2)
				sourceX = 1;
			currFrame = 0;
		}
		
	}


	if (col > indexCol)
	{
		spriteCurrRow = FOR_LEFT;
		x -= speed;
		if ((x+width-xOffSet) < (indexCol+1) * TILE_WIDTH)
		{
			col = indexCol;
			count++;
		}

		if (++currFrame >= frameDelay)
		{
			if (++sourceX > 2)
				sourceX = 1;
			currFrame = 0;
		}
	
	}
}


void Enemy::render()
{
		
	al_draw_bitmap_region(enemySprite, sourceX*width, spriteCurrRow*height, width, height, x, y, 0);

}


bool Enemy::collided(GameObject *Player)
{


	bool xCollision = false;
	bool yCollision = false;
	
	int direction = player->getDir();

	switch (direction)
	{

	case GOING_RIGHT:
		xCollision = player->getX() + TILE_WIDTH > x && player->getX() + TILE_WIDTH < x + TILE_WIDTH;
		yCollision = player->getY() + yOffSet > y && player->getY() + yOffSet < y + TILE_HEIGHT;
		break;

	case GOING_LEFT:
		xCollision = player->getX() > x && player->getX() < x + TILE_WIDTH;
		yCollision = (player->getY() + (TILE_HEIGHT / 2) > y) &&
			(player->getY() + (TILE_HEIGHT / 2) < y + TILE_HEIGHT);
			break;

	case GOING_UP:
		xCollision = player->getX() + xOffSet > x && player->getX() + xOffSet < x + TILE_WIDTH;
		yCollision = player->getY() > y && player->getY() < y + TILE_HEIGHT - yOffSet;
			break;
	
	case GOING_DOWN:
		xCollision = player->getX() + xOffSet > x && player->getX() + xOffSet < x + TILE_WIDTH;
		yCollision = player->getY() + TILE_HEIGHT > y && player->getY() + TILE_HEIGHT < y + TILE_HEIGHT;
			break;
	}

	return xCollision&&yCollision;
}


int Enemy::getID()
{
	return ENEMY;
}


