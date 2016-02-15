#include"StartMenuAct.h"


StartMenuAct::StartMenuAct(int x, int y, GameManager *gm, const ALLEGRO_FONT * gameTitleFont, const ALLEGRO_FONT *actionMsgFont, const char* gameTitle, const char * actionMsg)
{	
	MenuParent::init(x,y,gm,gameTitleFont,actionMsgFont,gameTitle,actionMsg);	
}


StartMenuAct::~StartMenuAct()
{
	delete actionMsg;
	delete gameTitle;
}


void StartMenuAct::onKeyEscape()
{
	gm->switchActivity(ACT_EXIT);
}


void StartMenuAct::onKeySpace()
{
	gm->switchActivity(ACT_GAME);
}


void StartMenuAct::render()
{
	al_draw_text(gameTitleFont, al_map_rgb(0, 60, 85), x+100, y, 0, gameTitle);
	al_draw_text(actionMsgFont, al_map_rgb(255, 255, 255), x-100, y+300, 0,actionMsg);
}