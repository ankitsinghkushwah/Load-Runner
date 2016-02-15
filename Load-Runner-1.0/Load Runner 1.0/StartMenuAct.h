//Header guards avoids double inclusion of the header file

#ifndef START_MENU_ACT_H
#define START_MENU_ACT_H


#include"MenuParent.h"
#include"GLOBALS.h"

class StartMenuAct : public MenuParent
{

public:

	StartMenuAct(int x,int y,GameManager *gm,const ALLEGRO_FONT* gameTitleFont,const ALLEGRO_FONT* actionMsgFont,const char* gameTitle,const char * acionMsg);
	~StartMenuAct();
	void onKeySpace();
	void onKeyEscape();
	void render();
};



#endif
