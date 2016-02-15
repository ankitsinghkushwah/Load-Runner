//Header guards avoids double inclusion of the header file

#ifndef GAME_WON_ACT_H
#define GAME_WON_ACT_H

#include"MenuParent.h"
#include"GLOBALS.h"

class GameWonAct : public MenuParent
{

public:

	GameWonAct(int x,int y,GameManager *gm,const ALLEGRO_FONT* gameTitleFont,const ALLEGRO_FONT* actionMsgFont,const char* gameTitle,const char * acionMsg);
	~GameWonAct();
	void onKeySpace();
	void onKeyEscape();
	void render();
};

#endif