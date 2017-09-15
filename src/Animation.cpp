#include "Animation.h"



Animation::Animation()
{
}
Animation::Animation(Texture &t,int x, int y, int w, int h, int count, float speed) {
	this->w = w;
	this->h = h;
	frame = 0;
	this->speed = speed;
	for (int i = 0; i < count; i++) 
		frames.push_back(IntRect(x+i*w, y, w, h));
	sprite.setTexture(t);
	sprite.setTextureRect(frames[0]);
}
void Animation::update() {
	frame += speed;
	int size = frames.size();
	if (frame >= size) frame -= size;
	if (size > 0) sprite.setTextureRect(frames[(int)frame]);
}
Sprite& Animation::get_sprite() {
	return sprite;
}

bool Animation::isEnd()
{
	return frame + speed >= frames.size();
}

Animation::~Animation()
{
}
