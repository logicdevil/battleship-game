#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Animation {
	float frame, speed;
	Sprite sprite;
	std::vector<IntRect> frames;
	
public:
	int w, h;
	Animation();
	Animation(Texture & t,int x, int y, int w, int h, int count, float speed);
	void update();
	Sprite & get_sprite();
	bool isEnd();
	~Animation();
};

