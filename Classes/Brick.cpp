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
	Brick->Type = type;
	switch (type)
	{
	case BrickType::Invisible:
		Brick->sprite = Sprite::create("GameObjects/Invibisle.png");
		break;

	case BrickType::EmptyGround:
		Brick->sprite = Sprite::create("GameObjects/Empty.png");
		break;
	case BrickType::GlassGreen:
		Brick->sprite = Sprite::create("GameObjects/Glass_Green.png");
		break;
	case BrickType::GlassRed:
		Brick->sprite = Sprite::create("GameObjects/Glass_Red.png");
		break;
	case BrickType::WaterHead:
		Brick->sprite = Sprite::create("GameObjects/Water_Head.png");
		break;
	case BrickType::Water:
		Brick->sprite = Sprite::create("GameObjects/Water.png");
		break;

	case BrickType::TreeRed:
		Brick->sprite = Sprite::create("GameObjects/Tree_Red.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.21));
		break;
	case BrickType::TreeGreen:
		Brick->sprite = Sprite::create("GameObjects/Tree_Green.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.21));
		break;
	case BrickType::TreeYellow:
		Brick->sprite = Sprite::create("GameObjects/Tree_Yellow.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.21));
		break;

	case BrickType::AuraRed:
		Brick->sprite = Sprite::create("GameObjects/Invibisle.png");
		break;
	case BrickType::AuraGreen:
		Brick->sprite = Sprite::create("GameObjects/Invibisle.png");
		break;
	case BrickType::AuraYellow:
		Brick->sprite = Sprite::create("GameObjects/Invibisle.png");
		break;

	case BrickType::Log:
		Brick->sprite = Sprite::create("GameObjects/log.png");
		break;
	case BrickType::Basket:
		Brick->sprite = Sprite::create("GameObjects/Basket.png");
		break;

	case BrickType::RopeHead:
		Brick->sprite = Sprite::create("GameObjects/Rope_Head.png");;
		break;
	case BrickType::Rope:
		Brick->sprite = Sprite::create("GameObjects/Rope.png");;
		break;
	}
	Brick->sprite->setPosition(location);
	return Brick;
}