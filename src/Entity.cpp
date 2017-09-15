#include "Entity.h"
Entity::Entity(int life) { this->life = life; }
Entity::Entity()
{
	this->life = 1;
}
void Entity::settings(Animation &a, int x, int y, float angle = 0, int radius = 1) {
	this->x = x;
	this->y = y;
	animation = a;
	this->angle = angle;
	R = radius;
	dx = dy = 0;
}

void Entity::update()
{
}
void Entity::draw(RenderWindow &app) {
	animation.get_sprite().setPosition(x, y);
	animation.get_sprite().setRotation(angle);
	app.draw(animation.get_sprite());
}

Animation& Entity::get_animation() {
	return animation;
}
int Entity::get_life() {
	return life;
}
void Entity::kill() {
	life = 0;
}
std::string Entity::get_name() {
	return name;
}
float Entity::get_angle() {
	return angle;
}
FloatRect Entity::get_rect() {
	return FloatRect(x, y, animation.w, animation.h);
}
Vector2f Entity::get_position() {
	return Vector2f(x, y);
}
Entity::~Entity()
{
}
