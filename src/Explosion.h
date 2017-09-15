#pragma once
#include "Entity.h"
class Explosion :
	public Entity
{
public:
	Explosion();
	Explosion(std::string name);
	void update();
	~Explosion();
};

