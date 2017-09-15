#pragma once
#include "Bullet.h"
class Missile :
	public Bullet
{
public:
	bool z_pressed;
	Missile();
	void set_position(Vector2f);
	void update();
	~Missile();
};

