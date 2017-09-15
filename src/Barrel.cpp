#include "Barrel.h"



Barrel::Barrel()
{
	name = "barrel";
}
void Barrel::settings(Animation &a, int x, int y, float angle = 0, int radius = 1) {
	this->x = x;
	this->y = y;
	animation = a;
	this->angle = angle;
	R = radius;
	animation.get_sprite().setOrigin(animation.w/15, animation.h/2);
	animation.get_sprite().setScale(0.6, 0.6);
	d_angle = 0.5;
	fire = 0;
}
void Barrel::update() {
	if (angle > 350)
		d_angle = -0.5;
	if (angle < 190)
		d_angle = 0.5;
	angle += d_angle;
	dx = -0.5f;
	x += dx;
	if (x < -100) life = 0;
	fire += 1+rand()%10;
}
Barrel::~Barrel()
{
}
