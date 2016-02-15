//Header guards avoids double inclusion of the header file


#ifndef MENU_PARENT_H
#define MENU_PARENT_H

//Presenting you the dumbest idea with inheritance

#include"GameManager.h"
#include"GLOBALS.h"


class MenuParent : public GameObject
{
protected:

	int x;
	int y;
	char *gameTitle;
	char * actionMsg;
	const ALLEGRO_FONT *gameTitleFont;
	const ALLEGRO_FONT *actionMsgFont;

	GameManager *gm;


public:
	void init(int x,int y,GameManager * gm,const ALLEGRO_FONT *gameTitleFont,const ALLEGRO_FONT * actionMsgFont,const char* gameTitle,const char* actionMsg);
	virtual void onKeySpace() = 0;
	virtual void onKeyEscape() = 0;
	virtual void render() = 0;
};

#endif
