#include"ActivityGame.h"

ActivityGame::ActivityGame(GameManager *gm) :player(0), mapObj(0)
{
	this->gm = gm;
	//MAP
	int map[ROWS*COLUMNS] =
	{
		1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		2,0,1,0,1,0,1,0,1,0,1,2,1,0,1,0,1,0,1,0,1,0,2,0,1,0,1,0,1,0,1,0,1,2,1,0,1,0,1,0,1,0,1,0,
		2,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,
		2,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,
		2,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,
		1,0,2,0,1,0,1,0,1,2,1,0,1,0,1,0,1,0,1,0,1,0,1,0,2,0,1,0,1,0,1,2,1,0,1,0,1,0,1,0,1,0,1,0,
		3,3,2,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,2,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,2,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,
		1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,

	};


	//Treasures row and cols

	int treasuresPos[MAX_TREASURES][2] =
	{
		{ 3,3 },
		{ 7,5 },
		{ 11,4 },
		{11,39},
		{11,4},
		{7,27},
		{3,42},
		{3,30},
		{11,26},
		{11,33}
	};

	int enemyPos[MAX_ENEMIES][5] = 
	{
		{3,20},
		{11,20},
		{ 3,30 },
		{ 11,35 },
		{ 11,35 }
			};

	sprites[TILES] = al_load_bitmap("Resources/sprite_tiles.png");
	mapObj = new Map(sprites[TILES],map);
	assert(mapObj!=0);
	 
	sprites[PLAYER] = al_load_bitmap("Resources/sprite_player.png");
	al_convert_mask_to_alpha(sprites[PLAYER],al_map_rgb(255,255,255));
	player = new Player(sprites[PLAYER],map,11,0);
	assert(player != 0);

	sprites[ENEMY] = al_load_bitmap("Resources/sprite_enemy.png");
	al_convert_mask_to_alpha(sprites[ENEMY],al_map_rgb(255,255,255));
	

	sprites[TREASURE_IMG] = al_load_bitmap("Resources/treasure.png");
	
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemy[i] = new Enemy(sprites[ENEMY], map, player, enemyPos[i][0], enemyPos[i][1], FOR_LEFT);
	}


	for (int i = 0; i < MAX_TREASURES; i++)
	{
		treasures[i] = new Treasure(treasuresPos[i][0], treasuresPos[i][1], sprites[TREASURE_IMG]);
	} 

	scoreBoard = new ScoreBoard(gm->getFontSmallSize(),MAX_TREASURES);


		//pushing objects in list
		objs.push_back(mapObj); 
		
		objs.push_back(scoreBoard);

		for (int i = 0; i < MAX_TREASURES; i++)
		{
			objs.push_back(treasures[i]);
		}

		objs.push_back(player);
		
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			objs.push_back(enemy[i]);
		}

		camera.init(player);
		scoreBoard->updatePos(player->getX(),player->getY());

		sm = new SoundManager;
		sm->play_music("resources/music/goonies.mp3");
	
}


ActivityGame::~ActivityGame()
{

	delete sm;
	
	//destroying sprites
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if(sprites[i]!=0)
		al_destroy_bitmap(sprites[i]);
	}

	for (GameObject * gameObj : objs)
		delete gameObj;
	objs.clear();
}


void ActivityGame::update() 
{

	for (auto iter = objs.begin(); iter != objs.end();)
	{
		if ((*iter)->collided(player) == true)
		{
			if ((*iter)->getID() == TREASURE)
			{
				scoreBoard->plusTreasure();
				delete *iter;
				iter = objs.erase(iter);

				if(scoreBoard->getTreasures() == MAX_TREASURES)
				{
					gm->switchActivity(ACT_GAMEWON);
					break;
				}
			}
			else if((*iter)->getID() == ENEMY)
			{
				gm->switchActivity(ACT_GAMEOVER);
				iter++;
			}
		}
		else
			iter++;
	}

	for (GameObject* gameObj : objs)
		gameObj->update();

	camera.updateCamera();
	
}


void ActivityGame::render()
{
	for (GameObject* gameObj : objs)
		gameObj->render();
}


void ActivityGame::onKeyDown()
{
	for (GameObject* gameObj : objs)
		gameObj->onKeyDown();
}


void ActivityGame::onKeyUp()
{
	for (GameObject* gameObj : objs)
		gameObj->onKeyUp();
}


void ActivityGame::onKeyRight()
{
	for (GameObject* gameObj : objs)
		gameObj->onKeyRight();
}


void ActivityGame::onKeyLeft()
{
	for (GameObject* gameObj : objs)
		gameObj->onKeyLeft();
}


void ActivityGame::onKeyReleased()
{
	for (GameObject* gameObj : objs)
		gameObj->onKeyReleased();
}


void ActivityGame::onKeyEscape()
{
	gm->switchActivity(ACT_STARTMENU);
}