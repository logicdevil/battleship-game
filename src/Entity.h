#pragma once
#include <string>
#include "Animation.h"
class Entity {
protected:
	float x, y, dx = 0, dy = 0, R, angle;
	int life;
	std::string name;
	Animation animation;
public:
	int fire;
	int id;
	Entity(int life);
	Entity();
	void settings(Animation & a, int x, int y, float angle, int radius);
	virtual void update();
	void draw(RenderWindow & app);
	Animation & get_animation();
	int get_life();
	void kill();
	std::string get_name();
	float get_angle();
	FloatRect get_rect();
	Vector2f get_position();
	~Entity();
};

