//Header guards avoids double inclusion of the header file
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

//STANDARD C++ HEADERS
#include<list>

//THIRD PARTY HEADERS
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_ttf.h>

//USER DEFINED HEADERS
#include"GameObject.h"
#include"GLOBALS.h"


class GameManager
{

	//compile time const
	static const int MAX_FONTS = 3;

	//Types in fonts
	enum Fonts { LARGE, MEDIUM, SMALL };


	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font[3];

	GameObject *currentActObj;
	Acts currentAct;

	bool gameDone;
	bool actSwitched;
	bool draw;
	bool keys[6];

public:


	GameManager();
	~GameManager();

	ALLEGRO_FONT *getFontSmallSize() 
	{ 
		return font[MEDIUM]; 
	}

	bool initialize();
	void switchActivity(Acts activity);
	void initCurrentActObjs();
	void start();
};

#endif
