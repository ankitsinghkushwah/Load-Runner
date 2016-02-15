

#include"GameManager.h"
#include"StartMenuAct.h"
#include"ActivityGame.h"
#include"GameOverAct.h"
#include"GameWonAct.h"


//Contructor will initialize all the objects to zero
GameManager::GameManager() :display(0), event_queue(0),timer(0),currentActObj(0)
{
	for (int i = 0; i < MAX_FONTS; i++)
		font[i] = 0;
}

//Our destructor will destroy the allocated memory
GameManager::~GameManager() 
{
	for (int i = 0; i < 3; i++)
	{
		if(font[i]!=0)
		al_destroy_font(font[i]);
	}

	if(event_queue!=0)
	al_destroy_event_queue(event_queue);
	if(timer!=0)
	al_destroy_timer(timer);
	if(display!=0)
	al_destroy_display(display);
}


bool GameManager::initialize()
{
	if (!al_init())
	{
		al_show_native_message_box(0,0,"ERROR!!","failed to initalize allegro!!",0,0);
		return false;
	}

	//Creating a display
	display = al_create_display(WIDTH,HEIGHT);
	
	if (!display)
	{
		al_show_native_message_box(0, 0, "ERROR!!", "failed to create display!!", 0, 0);
		return false;
	}

	al_set_window_position(display,0,0);

	//Initializing all the addons
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	
	//Loading different size fonts for our game 
	font[LARGE] = al_load_font("Resources/font.ttf", 60, 0);
	assert(font[LARGE] != 0);  //only one assert is needed 

	font[MEDIUM] = al_load_font("Resources/font.ttf", 48, 0);
	 
	font[SMALL] = al_load_font("Resources/font.ttf", 12, 0);
	
	//Creating event queue
	event_queue = al_create_event_queue();
	
	//Setting timer to 60 frames per second
	timer = al_create_timer(1.0/(float)FPS);
	
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue,al_get_timer_event_source(timer));

	gameDone = false;
	actSwitched = false;

	//Setting current activity to start menu
	currentAct = ACT_STARTMENU;
	
	for (int i = 0; i < 6; i++)
		keys[i] = false;
	
	draw = false;
	
	return true;
}


void GameManager::switchActivity(Acts nextAct)
{
	currentAct = nextAct;
	actSwitched = true;
}


void GameManager::initCurrentActObjs()
{
	switch (currentAct)
	{
	case ACT_STARTMENU:
		currentActObj = new StartMenuAct(250,100,this, font[0], font[1],"L o a d  R u n n e r","press space to play and escape to exit");
		actSwitched = false;
 		break;
	case ACT_GAME:
		currentActObj = new ActivityGame(this);
		actSwitched = false;
		break;
	case ACT_GAMEOVER:
		currentActObj = new GameOverAct(250, 100, this, font[0], font[1], "GAMEOVER!", "press space to play again and escape to exit");
		actSwitched = false;
		break;
	case ACT_GAMEWON:
		currentActObj = new GameWonAct(250, 100, this, font[0], font[1], "YOU NAILED IT", "press space to play again and escape to exit");
		actSwitched = false;
		break;
	case ACT_EXIT:
		gameDone = true;
		actSwitched = true;
		break;
	}

}


void GameManager::start()
{
	do
	{
		//Initializing current activity objects
		initCurrentActObjs();
		
		for (int i = 0; i < 6; i++)
			keys[i] = false;
		
		al_start_timer(timer);

		/* ===============================================
						      GAME LOOP
		   =============================================== */

		while(!actSwitched)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(event_queue,&event);

			if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					break;
				case ALLEGRO_KEY_ESCAPE:
					keys[ESCAPE] = true;
					break;
				}
			}
			else if (event.type == ALLEGRO_EVENT_KEY_UP)
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					keys[ESCAPE] = false;
					break;
					
				}

				currentActObj->onKeyReleased();
			}
			else if (event.type == ALLEGRO_EVENT_TIMER)
			{
				if (keys[SPACE])
					currentActObj->onKeySpace();
				if(keys[LEFT])
					currentActObj->onKeyLeft();
				if (keys[RIGHT])
					currentActObj->onKeyRight();
				if (keys[UP])
					currentActObj->onKeyUp();
				if (keys[DOWN])
					currentActObj->onKeyDown();
				if (keys[ESCAPE])
					currentActObj->onKeyEscape();

				currentActObj->update();
				
				draw = true;
			}
			if (draw)
				currentActObj->render();
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			
		}

		if (!gameDone && actSwitched)
		{
			al_stop_timer(timer);
			delete currentActObj;
		}

	} while (!gameDone);
}
