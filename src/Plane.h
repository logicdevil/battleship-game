#pragma once
#include "Entity.h"
class Plane :
	public Entity
{
	float maxSpeed;
public:
	Plane();
	void update();
	void keyPressed(Keyboard::Key code);
	void keyReleased(Keyboard::Key code);
	void set_position(Vector2f v);
	void set_life();
	~Plane();
};

