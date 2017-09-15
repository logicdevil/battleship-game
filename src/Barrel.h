#pragma once
#include "Entity.h"
class Barrel : public Entity
{
	float d_angle;
public:
	Barrel();
	void settings(Animation & a, int x, int y, float angle, int radius);
	void update();
	~Barrel();
};

