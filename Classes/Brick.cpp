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
	case BrickType::EmptyGround:
		Brick->sprite = Sprite::create("GameObjects/Block_Empty.png");
		break;
	case BrickType::GlassGreen:
		Brick->sprite = Sprite::create("GameObjects/Block_Glass_Green.png");
		break;
	case BrickType::GlassRed:
		Brick->sprite = Sprite::create("GameObjects/Block_Glass_Red.png");
		break;
	case BrickType::TreeGreen:
		Brick->sprite = Sprite::create("GameObjects/Tree_Green.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.21));
		break;
	case BrickType::TreeRed:
		Brick->sprite = Sprite::create("GameObjects/Tree_Red.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.21));
		break;
	case BrickType::Invisible:
		Brick->sprite = Sprite::create("GameObjects/Invibisle.png");
	}
	Brick->sprite->setPosition(location);
	return Brick;
}