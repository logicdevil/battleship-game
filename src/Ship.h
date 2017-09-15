#pragma once
#include "Entity.h"
#include "Barrel.h"
#include "Explosion.h"
class Ship :
	public Entity
{
public:
	Barrel* b1, *b2, *b3, *b4, *b5;
	Ship();
	void update();
	~Ship();
};

