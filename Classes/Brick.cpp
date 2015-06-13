#include "Brick.h"

USING_NS_CC;

CBrick::CBrick()
{
}


CBrick::~CBrick()
{
}

CBrick* CBrick::Create(BrickType type, CGameObject::Pallets revelation, LayerZOrders zorder)
{
	auto Brick = new CBrick();
	Brick->Type = type;
	switch (type)
	{
	case BrickType::Air:
		Brick->sprite = Sprite::create("GameObjects/Invibisle.png");
		break;
	case BrickType::Invisible:
		Brick->sprite = Sprite::create("GameObjects/Invibisle.png");
		break;

	case BrickType::EmptyGround:
		Brick->sprite = Sprite::create("GameObjects/Empty.png");
		break;
	case BrickType::GlassGreen:
		Brick->sprite = Sprite::create("GameObjects/Glass_Green.png");
		Brick->isDestroy = true;
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
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.25));
		break;
	case BrickType::TreeGreen:
		Brick->sprite = Sprite::create("GameObjects/Tree_Green.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.25));
		break;
	case BrickType::TreeYellow:
		Brick->sprite = Sprite::create("GameObjects/Tree_Yellow.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.25));
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
		Brick->sprite->setAnchorPoint(Vec2(0.83, 0.5));
		Brick->SetAdditional(Vec2(-1, 0));
		Brick->SetAdditional(Vec2(1, 0));
		Brick->isGraviry = true;
		break;
	case BrickType::Basket:
		Brick->sprite = Sprite::create("GameObjects/Basket.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.8));
		break;

	case BrickType::RopeHead:
		Brick->sprite = Sprite::create("GameObjects/Rope_Head.png");;
		break;
	case BrickType::Rope:
		Brick->sprite = Sprite::create("GameObjects/Rope.png");;
		break;
	}
	Brick->RevelationColor = revelation;
	Brick->zOrder = zorder;
	return Brick;
}