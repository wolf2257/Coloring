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
		Brick->sprite = Sprite::create("gameobjects/invibisle.png");
		break;
	case BrickType::Invisible:
		Brick->sprite = Sprite::create("gameobjects/invibisle.png");
		break;

	case BrickType::EmptyGround:
		Brick->sprite = Sprite::create("gameobjects/empty.png");
		break;
	case BrickType::GlassGreen:
		Brick->sprite = Sprite::create("gameobjects/glass_green.png");
		Brick->isDestroy = true;
		break;
	case BrickType::GlassRed:
		Brick->sprite = Sprite::create("gameobjects/glass_red.png");
		break;
	case BrickType::WaterHead:
		Brick->sprite = Sprite::create("gameobjects/water_head.png");
		break;
	case BrickType::Water:
		Brick->sprite = Sprite::create("gameobjects/water.png");
		break;

	case BrickType::TreeRed:
		Brick->sprite = Sprite::create("gameobjects/tree_red.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.25));
		break;
	case BrickType::TreeGreen:
		Brick->sprite = Sprite::create("gameobjects/tree_green.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.25));
		break;
	case BrickType::TreeYellow:
		Brick->sprite = Sprite::create("gameobjects/tree_yellow.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.25));
		break;

	case BrickType::AuraRed:
		Brick->sprite = Sprite::create("gameobjects/invibisle.png");
		break;
	case BrickType::AuraGreen:
		Brick->sprite = Sprite::create("gameobjects/invibisle.png");
		break;
	case BrickType::AuraYellow:
		Brick->sprite = Sprite::create("gameobjects/invibisle.png");
		break;

	case BrickType::Log:
		Brick->sprite = Sprite::create("gameobjects/log.png");
		Brick->sprite->setAnchorPoint(Vec2(0.83, 0.5));
		Brick->SetAdditional(Vec2(-1, 0));
		Brick->SetAdditional(Vec2(1, 0));
		Brick->isGraviry = true;
		break;
	case BrickType::Basket:
		Brick->sprite = Sprite::create("gameobjects/basket.png");
		Brick->sprite->setAnchorPoint(Vec2(0.5, 0.8));
		break;

	case BrickType::RopeHead:
		Brick->sprite = Sprite::create("gameobjects/rope_head.png");;
		break;
	case BrickType::Rope:
		Brick->sprite = Sprite::create("gameobjects/rope.png");;
		break;
	}
	Brick->RevelationColor = revelation;
	Brick->zOrder = zorder;
	return Brick;
}