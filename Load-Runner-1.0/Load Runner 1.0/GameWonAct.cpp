#include"GameWonAct.h"

#include"GameWonAct.h"


GameWonAct::GameWonAct(int x, int y, GameManager *gm, const ALLEGRO_FONT * gameTitleFont, const ALLEGRO_FONT *actionMsgFont, const char* gameTitle, const char * actionMsg)
{	
	MenuParent::init(x,y,gm,gameTitleFont,actionMsgFont,gameTitle,actionMsg);	
}


GameWonAct::~GameWonAct()
{
	delete actionMsg;
	delete gameTitle;
}


void GameWonAct::onKeyEscape()
{
	gm->switchActivity(ACT_EXIT);
}


void GameWonAct::onKeySpace()
{
	gm->switchActivity(ACT_GAME);
}

void GameWonAct::render()
{
	al_draw_text(gameTitleFont, al_map_rgb(0, 60, 85), x+100, y, 0, gameTitle);
	al_draw_text(actionMsgFont, al_map_rgb(255, 255, 255), x-100, y+300, 0,actionMsg);
}