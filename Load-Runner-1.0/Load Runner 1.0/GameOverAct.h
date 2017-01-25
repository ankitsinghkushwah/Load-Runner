#ifndef GAME_OVER_ACT_H
#define GAME_OVER_ACT_H

#include"MenuParent.h"
#include"GLOBALS.h"
#include"SoundManager.h"

class GameOverAct : public MenuParent
{

	SoundManager *sm;
public:

	GameOverAct(int x,int y,GameManager *gm,const ALLEGRO_FONT* gameTitleFont,const ALLEGRO_FONT* actionMsgFont,const char* gameTitle,const char * acionMsg);
	~GameOverAct();
	void onKeySpace();
	void onKeyEscape();
	void render();
};

#endif