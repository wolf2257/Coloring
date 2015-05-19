#include "Brick.h"

USING_NS_CC;

CBrick::CBrick()
{
}


CBrick::~CBrick()
{
}

CBrick CBrick::Create(BrickType type, Vec2 location)
{
	auto Brick = CBrick();
	switch (type)
	{
	case CBrick::Empty:
		Brick.sprite = Sprite::create("gamescene/ground/empty.png");
		break;
	case CBrick::Glass:
		Brick.sprite = Sprite::create("gamescene/ground/glass.png");
		break;
	default:
		//return nullptr;
		break;
	}
	Brick.sprite->setPosition(location);
	return Brick;
}

void CBrick::Attatch(Layer *layer, int zOrder)
{
	layer->addChild(this->sprite, zOrder);
}