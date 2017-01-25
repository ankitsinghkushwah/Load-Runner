//Header guards avoids double inclusion of the header file

#ifndef ACTIVITY_GAME_H
#define ACTIVITY_GAME_H


#include<list>

#include"GameObject.h"
#include"Map.h"
#include"Player.h"
#include"Enemy.h"
#include"GameManager.h"
#include"Treasure.h"
#include"ScoreBoard.h"
#include"Camera.h"
#include"SoundManager.h"


class ActivityGame : public GameObject
{


	SoundManager *sm;
	//compile time constants
	static const int MAX_SPRITES = 4;
	static const int MAX_TREASURES = 10;
	static const int MAX_ENEMIES = 5;
	enum EnspriteCurrRow { PLAYER, ENEMY, TILES ,TREASURE_IMG};

	std::list<GameObject*> objs;
	
	//Objects in this activity
	
	Map *mapObj;
	Camera camera;
	Player *player;
	Enemy *enemy[MAX_ENEMIES];
	Treasure *treasures[MAX_TREASURES];
	ScoreBoard *scoreBoard;
	
	
	//going to need this one for to switch activity
	GameManager *gm;

	ALLEGRO_BITMAP *sprites[MAX_SPRITES];
	
public:

	ActivityGame(GameManager* gm);
	~ActivityGame();

	void onKeyUp();
	void onKeyDown();
	void onKeyLeft();
	void onKeyRight();
	void onKeyReleased();
	void onKeyEscape();

	void update();
	void render();

	bool collided(GameObject* player)
	{
		return false;
	}
};

#endif
