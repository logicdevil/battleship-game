#include "Explosion.h"


Explosion::Explosion()
{
}
Explosion::Explosion(std::string n)
{
	name = n;
}
void Explosion::update() {	
	if(name.compare("shield"))
		dx = -0.5f;	
	x += dx;
	if (x < -650) life = 0;
	
}


Explosion::~Explosion()
{
}
