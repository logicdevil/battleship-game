#include "Plane.h"



Plane::Plane() : Entity(3)
{
	name = "plane";
	maxSpeed = 10;
}
void Plane::update() {
	float prev_x = x;
	float prev_y = y;
	x += dx;
	y += dy;
	if (x > 1366-125 || x < 0 || y < 0) {
		x = prev_x;
		y = prev_y;
		dx = 0; dy = 0;
	}
	if (y > 600 - 36) life = 0;
	
}
void Plane::keyReleased(Keyboard::Key code) {
	switch (code) {
	case Keyboard::Left:
			if (dx < -0.1f)
				dx += 0.2f;
			else if (dx < 0.1f) dx = 0;
		break;
	case Keyboard::Right:
			if (dx > 0.1f)
				dx -= 0.2f;
			else if (dx > -0.1) dx = 0;
		break;
	case Keyboard::Down:
		if(dy > 0.1f)
			dy -= 0.2f;
		else if (dy > -0.1f) dy = 0;
		break;
	case Keyboard::Up:
		if(dy < -0.1f) 
			dy += 0.2f;
		else if (dy < 0.1f) dy = 0;
		break;
	default:
		break;
	}

}
void Plane::keyPressed(Keyboard::Key code) {
	switch (code) {
	case Keyboard::Left:
		if(dx > -maxSpeed)
			dx -= 0.2f;
		break;
	case Keyboard::Right:
		if (dx < maxSpeed)
			dx += 0.4f;
		break;
	case Keyboard::Down:
		if (dy < maxSpeed)
			dy += 0.4f;
		break;
	case Keyboard::Up:
		if (dy > -maxSpeed)
			dy -= 0.2f;
		break;
	default:
		break;
	}
}
void Plane::set_position(Vector2f v) {
	x = v.x;
	y = v.y;
}
void Plane::set_life() {
	life = 1;
}

Plane::~Plane()
{
}
