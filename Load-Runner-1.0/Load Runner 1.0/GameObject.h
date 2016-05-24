//Header guards avoids double inclusion of the header file


#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
	virtual ~GameObject() {}

	virtual void onKeyLeft() {}
	virtual void onKeyRight() {}
	virtual void onKeyUp() {}
	virtual void onKeyDown() {}
	virtual void onKeySpace() {}
	virtual void onKeyReleased() {}
	virtual void onKeyEscape() {}
	
	virtual int getDir() { return 0; }
	virtual int getX() { return 0; }
	virtual int getY() { return 0; }

	virtual bool collided(GameObject* player){ return false; }
	virtual int getID() { return -1; }

	virtual void update() {}
	virtual void render() {}
};

#endif
