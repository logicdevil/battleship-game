#include "Ship.h"



Ship::Ship()
{
	name = "ship";
	b1 = new Barrel();
	b2 = new Barrel();
	b3 = new Barrel();
	b4 = new Barrel();
	b5 = new Barrel();
	fire = 0;



}
void Ship::update() {
	dx = -0.5f;
	x += dx;
	if (x < -650) life = 0;
}

Ship::~Ship()
{
}
