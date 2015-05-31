#include "Brick.h"

USING_NS_CC;

CBrick::CBrick()
{
}


CBrick::~CBrick()
{
}

CBrick* CBrick::Create(BrickType type, Vec2 location)
{
	auto Brick = new CBrick();
	switch (type)
	{
	case CBrick::Empty:
		Brick->sprite = Sprite::create("GameObjects/Block_Empty.png");
		break;
	case CBrick::GlassGreen:
		Brick->sprite = Sprite::create("GameObjects/Block_Glass_Green.png");
		break;
	case CBrick::GlassRed:
		Brick->sprite = Sprite::create("GameObjects/Block_Glass_Red.png");
		break;
	default:
		//return nullptr;
		break;
	}
	Brick->sprite->setPosition(location);
	return Brick;
}

void CBrick::Attatch(Layer *layer, int zOrder)
{
	layer->addChild(this->sprite, zOrder);
}