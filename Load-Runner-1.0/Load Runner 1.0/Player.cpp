#include"Player.h"

Player::Player() {}


Player::Player(ALLEGRO_BITMAP *playerSprite, int map[],int curRow,int curCol) 
{
 	this->playerSprite = playerSprite;
	
	for (int i = 0; i < ROWS*COLUMNS; i++)
		this->map[i] = map[i];

	this->x = curCol*TILE_WIDTH;
	this->y = curRow*TILE_HEIGHT;
	this->width = TILE_WIDTH;
	this->height = TILE_HEIGHT;
	
	xOffSet = 19;
	yOffSet = 2;
	
	this->spriteCurrRow = FOR_RIGHT;
	
	sourceX = 0;
	canGo[LEFT] = true;
	canGo[RIGHT] = true;
	canGo[UP] = false;
	canGo[DOWN] = false;

	colliding = true;
	onLadder = false;
	currFrame = 0;
	frameDelay = 5;
	falling = false;

	x1Lim = y1Lim = x2Lim = y2Lim = 0;
	
	this->speed = 6;

	this->lastVertDir = FOR_DOWN;

}


Player::~Player()
{

}


void Player::onKeyLeft()
{
	if (canGo[LEFT])
	{
		canGo[RIGHT] = canGo[UP] = canGo[DOWN] = false;
		spriteCurrRow = FOR_LEFT;
		x -= speed;

		if (++currFrame >= frameDelay)
		{
			if (++sourceX > 2) sourceX = 1;
			currFrame = 0;
		}

		if (onLadder)
		{
			if (x + width-xOffSet < x1Lim)
			{
				onLadder = false;
				colliding = false;
				canGo[LEFT] = false;
			}
		}
	}
}


void Player :: onKeyRight()
{
	if (canGo[RIGHT])
	{
		canGo[LEFT] = canGo[UP] = canGo[DOWN] = false;
        spriteCurrRow = FOR_RIGHT;
		x += speed;
		if (++currFrame >= frameDelay)
		{
			if (++sourceX > 2) sourceX = 1;
			currFrame = 0;
		}

		if (onLadder)
		{
			if (x + xOffSet > x2Lim)
			{
				onLadder = false;
				colliding = false;
				canGo[RIGHT] = false;
			}
		}
	}
}


void Player::onKeyUp()
{
	if (canGo[UP])
	{
		canGo[LEFT] = canGo[RIGHT] = canGo[DOWN] = false;
		onLadder = true;
		colliding = true;
		spriteCurrRow = FOR_UP;
		lastVertDir = FOR_UP;
		y -= speed;
	

		if (++currFrame >= frameDelay)
		{
			if (++sourceX > 2) sourceX = 1;
			currFrame = 0;
		}

		if (y + height < y1Lim)
		{
			lastVertDir = FOR_DOWN;
			onLadder = false;
			colliding = false;
			canGo[UP] = false;
		}
	}
}


void Player::onKeyDown()
{
	if (canGo[DOWN])
	{
		canGo[LEFT] = canGo[UP] = canGo[RIGHT] = false;
		onLadder = true;
		colliding = true;
		spriteCurrRow = FOR_DOWN;

		//canGo[LEFT] = canGo[RIGHT] = false;

		lastVertDir = FOR_DOWN;

		y += speed;

		if (++currFrame >= frameDelay)
		{
			if (++sourceX > 2) sourceX = 1;
			currFrame = 0;
		}

		if (y+yOffSet > y2Lim)
		{
			onLadder = false;
			colliding = false;
			canGo[DOWN] = false;
		}
	}
}


void Player::onKeyReleased()
{
	canGo[LEFT] = canGo[UP] = canGo[DOWN] = canGo[RIGHT] = true;

	if (!falling && !onLadder)sourceX = 0;
}


void Player::update()
{
	

	if(!onLadder)
	{
		int tempY=y+height+yOffSet;
		colliding = collidingWithGround( spriteCurrRow==FOR_RIGHT ? ( x+xOffSet ) : ( x+width-xOffSet ) , tempY );
		if(colliding)
			y = tempY;
	}

	if(!colliding)
	{
		canGo[UP] = canGo[DOWN] = canGo[LEFT] = canGo[RIGHT] = false;
		falling = true;
		spriteCurrRow = FOR_FALL;
		
		//animate player is falling
		
		y+=speed;

		if(++currFrame>=frameDelay)
		{
			if(++sourceX>2)
				sourceX = 1;
			currFrame = 0;
		}
	}
	else
	{
		if(falling)
		{
			falling = false;
			sourceX = 0;
		}
	}


	if(!falling)
	{
		if (!onLadder)
		{
			int row = 0, col = 0;

			//checking if current pos has ladder and getting the row and col of that pos in map

			if (currPosHasLadder(spriteCurrRow == FOR_RIGHT ? x + xOffSet : x + width - xOffSet, (y + height / 2), row, col))
			{
				x1Lim = x-5;
				x2Lim = x + width + 5;
				y1Lim = getTopLimOfLadder(row, col);

				canGo[UP] = true;
			}
			else
			{
				y1Lim = y + height;
				canGo[UP] = false;
			}

			// checking if player can go down
			if (currPosHasLadder(spriteCurrRow == FOR_RIGHT ? x + xOffSet : x + width - xOffSet, (y + height + height / 2), row, col))
			{
				x1Lim = x-5;
				x2Lim = x + width + 5;
				y2Lim = getBottomLimOfLadder(row, col);

				canGo[DOWN] = true;
			}
			else
			{
				y2Lim = y;
				canGo[DOWN] = false;
			}
		}
			//checking if player doesnt have any obstacle in the right side
			if(wallIsAhead(x+width-xOffSet,lastVertDir == FOR_UP ? y+yOffSet : y+height-yOffSet) == false && x+width < (COLUMNS*TILE_WIDTH) )
				canGo[RIGHT] = true;
			else
			{
				//sourceX = 0;
				canGo[RIGHT] = false;
			}

			//cheking the same for left side
			if(wallIsAhead(x+xOffSet, lastVertDir == FOR_UP ? y + yOffSet : y + height- yOffSet) == false && x > 0)
				canGo[LEFT] = true;
			else
			{
				//sourceX = 0;
				canGo[LEFT] = false;
			}

		
	}
	
	
}


void Player::render()
{
	al_draw_bitmap_region(playerSprite,sourceX*width,spriteCurrRow*height,width,height,x,y,0);
}


bool Player::collidingWithGround(int x, int &y)
{
	for (int i = 0; i < ROWS*COLUMNS ; i++)
	{
		if (map[i] == LADDER || map[i] == FLOOR1 || map[i] == FLOOR2)
		{
			int tempX1 = (i%COLUMNS)*TILE_WIDTH;
			int tempX2 = ((i%COLUMNS)*TILE_WIDTH)+TILE_WIDTH;
			int tempY1 = (i/COLUMNS)*TILE_HEIGHT;
			int tempY2 = ((i/COLUMNS)*TILE_HEIGHT)+TILE_HEIGHT;

			if (x > tempX1 && x<tempX2 && y>tempY1 && y < tempY2)
			{
				y = tempY1-TILE_HEIGHT;
				return true;
			}
		}
	}
	return false;
}


bool Player::currPosHasLadder(int x, int y, int &row, int &col)
{
	for (int tempRow = 0; tempRow < ROWS; tempRow++)
	{
		for (int tempCol = 0; tempCol < COLUMNS; tempCol++)
		{
			if (map[blockNumber(tempRow, tempCol)] == LADDER)
			{
				
				int tempX1 = tempCol*TILE_WIDTH;
				int tempX2 = (tempCol*TILE_WIDTH)+TILE_WIDTH;
				int tempY1 = tempRow*TILE_HEIGHT;
				int tempY2 = (tempRow*TILE_HEIGHT)+TILE_HEIGHT;

				if (x > tempX1 && x<tempX2 && y>tempY1 && y < tempY2)
				{
					row = tempRow;
					col = tempCol;
					return true;
				}
			}
		}
	}
	return false;
}


bool Player::wallIsAhead(int x,int y)
{
	for (int tempRow = 0; tempRow < ROWS; tempRow++)
	{
		for (int tempCol = 0; tempCol < COLUMNS; tempCol++)
		{
			if (map[blockNumber(tempRow, tempCol)] == FLOOR1 || map[blockNumber(tempRow, tempCol)] == FLOOR2)
			{

				int floorX1 = tempCol*TILE_WIDTH;
				int floorX2 = (tempCol*TILE_WIDTH) + TILE_WIDTH;
				int floorY1 = tempRow*TILE_HEIGHT;
				int floorY2 = (tempRow*TILE_HEIGHT) + TILE_HEIGHT;

				if (x > floorX1 && x < floorX2 && y > floorY1 && y < floorY2)
					return true;
			}
		}
	}
	return false;
}


int Player::getTopLimOfLadder(int row, int col)
{
	int tempRow = row;
	while (true)
	{
		tempRow--;
		if (map[blockNumber(tempRow, col)] != LADDER)
			return ((++tempRow)*TILE_HEIGHT);
	}
	
	return false;
}


int Player::getBottomLimOfLadder(int row, int col)
{
	int tempRow = row;
	while (true)
	{
		tempRow++;
		if (map[blockNumber(tempRow, col)] != LADDER)
			return ((--tempRow)*TILE_HEIGHT);
	}

	return false;
}



int Player::getRow()
{
	int result_row = 0;
		
		if (spriteCurrRow == FOR_DOWN)
		{
			for (int row = 0; row < ROWS; row++)
			{
				if ( (y + yOffSet) > row*TILE_HEIGHT && (y + yOffSet) < row*TILE_HEIGHT + TILE_HEIGHT ) 
				{
					result_row = row;
				}
			}
		}
		else
		{
			for (int row = 0; row < ROWS; row++)
			{
				if ((y + height-yOffSet) > row*TILE_HEIGHT && (y + height-yOffSet) < row*TILE_HEIGHT + TILE_HEIGHT)
				{
					result_row = row;
				}
			}
		}
		
		return result_row;
	
}


int Player::getCol()
{
	int result_col = 0;

	if (spriteCurrRow == FOR_RIGHT)
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			if ((x + xOffSet) > col*TILE_WIDTH && (x + xOffSet) < col*TILE_WIDTH + TILE_WIDTH)
			{
				result_col = col;
			}
		}
	}
	else
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			if ((x + width - xOffSet) > col*TILE_WIDTH && (x + width - xOffSet) < col*TILE_WIDTH + TILE_WIDTH)
			{
				result_col= col;
			}
		}
	}

	return result_col;
}