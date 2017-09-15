#include "Bullet.h"
Bullet::Bullet() {}
Bullet::Bullet(std::string n)
{
	name = n;
}
void Bullet::update() {
	dx = cos(angle*0.017453f) * 15;
	dy = sin(angle*0.017453f) * 15;
	x += dx;
	y += dy;
	if (x > 1366 || x < 0 || y > 768 || y < 0) life = 0;
}


Bullet::~Bullet()
{
}

