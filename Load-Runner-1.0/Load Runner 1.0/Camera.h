//Header guards avoids double inclusion of the header file

#ifndef CAMERA_H
#define CAMERA_H

#include<allegro5/allegro.h>

#include"Player.h"
#include"GLOBALS.h"


class Camera
{
	int x;
	int y;
	Player *player;
	ALLEGRO_TRANSFORM camera;

public:
	void init(Player *player)
	{
		this->player = player;
		x = 0;
		y = 0;
	}

	void updateCamera()
	{
		x = player->getX()+TILE_WIDTH/2 - WIDTH/2;
		y = player->getY()+TILE_HEIGHT/2 - HEIGHT;

		if(x<0) x = 0;
		if(y<0) y = 0;
		if(x>WIDTH)
			x = WIDTH;
		

		al_identity_transform(&camera);
		al_translate_transform(&camera,-x,-y);
		al_use_transform(&camera);

	}

	Camera::~Camera()
	{
		al_identity_transform(&camera);
		al_translate_transform(&camera,0,0);
		al_use_transform(&camera);

	}
};
#endif