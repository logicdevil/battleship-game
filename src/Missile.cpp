#include "Missile.h"



Missile::Missile()
{
	name = "missile";
}
void Missile::set_position(Vector2f v) {
	this->x = v.x+60;
	this->y = v.y+36;
}
void Missile::update() {
	if (angle < 90)
	{
		if (z_pressed)
			angle += 2;
	}
		dx = cos(angle*0.017453f) * 8;
		dy = sin(angle*0.017453f) * 8;
	x += dx;
	y += dy;
	if (x > 1366 || x < 0 || y > 768-100 || y < 0) life = 0;
	if (y > 768 - 100) fire = 1;
}

Missile::~Missile()
{
}
