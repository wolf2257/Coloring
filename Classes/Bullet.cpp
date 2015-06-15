#include "Bullet.h"

USING_NS_CC;

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

CBullet* CBullet::Create(Direction dir, cocos2d::Vec2 location)
{
	auto Brick = new CBullet();
	Brick->sprite = Sprite::create("gameobjects/bullet.png");
	Brick->sprite->setPosition(location);
	Brick->direction = dir;
	Brick->zOrder = LayerZOrders::PlayerObjects;
	Brick->SetSpeed(7);
	return Brick;
}

void CBullet::Update(float dt)
{
	this->SetLocation(this->GetLocation() + Vec2((direction==Direction::Right) ? speed : -speed, 0));
}