#include"GameOverAct.h"


GameOverAct::GameOverAct(int x, int y, GameManager *gm, const ALLEGRO_FONT * gameTitleFont, const ALLEGRO_FONT *actionMsgFont, const char* gameTitle, const char * actionMsg)
{	
	MenuParent::init(x,y,gm,gameTitleFont,actionMsgFont,gameTitle,actionMsg);	
}


GameOverAct::~GameOverAct()
{
	delete actionMsg;
	delete gameTitle;
}


void GameOverAct::onKeyEscape()
{
	gm->switchActivity(ACT_EXIT);
}


void GameOverAct::onKeySpace()
{
	gm->switchActivity(ACT_GAME);
}

void GameOverAct::render()
{
	al_draw_text(gameTitleFont, al_map_rgb(196, 6, 11), x+200, y, 0, gameTitle);
	al_draw_text(actionMsgFont, al_map_rgb(255, 255, 255), x-100, y+400, 0,actionMsg);
}