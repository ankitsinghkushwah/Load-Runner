#include"MenuParent.h"

void MenuParent::init(int x,int y,GameManager * gm,const ALLEGRO_FONT *gameTitleFont,const ALLEGRO_FONT * actionMsgFont,const char* gameTitle,const char* actionMsg)
{
	this->x = x;
	this->y = y;
	this->gm = gm;
	this->actionMsgFont = actionMsgFont;
	this->gameTitleFont = gameTitleFont;
	
	this->actionMsg = new char[strlen(actionMsg)+1];
	strcpy(this->actionMsg,actionMsg);

	this->gameTitle = new char[strlen(gameTitle)+1];
	strcpy(this->gameTitle,gameTitle);
}


