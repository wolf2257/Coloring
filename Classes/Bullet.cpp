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
	Brick->sprite->setPosition(location);
	Brick->direction = dir;
	return Brick;
}

void CBullet::Update(float dt)
{
	this->SetLocation(this->GetLocation() + Vec2(0, this->speed * (direction==Direction::Right) ? 1 : -1));
}