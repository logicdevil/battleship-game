#pragma once
#include "Entity.h"
class Bullet :
	public Entity
{
public:
	Bullet();
	Bullet(std::string n);
	void update();
	~Bullet();
};

