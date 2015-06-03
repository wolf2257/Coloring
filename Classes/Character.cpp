#include "Character.h"

USING_NS_CC;

CCharacter::CCharacter()
{
}


CCharacter::~CCharacter()
{
}

CCharacter* CCharacter::Create(Vec2 location)
{
	auto chara = new CCharacter();
	chara->sprite = Sprite::create("Charactor/Stand.png");
	chara->sprite->setPosition(location);
	chara->SetSpeed(3);
	return chara;
}


void CCharacter::MoveLeft()
{
	this->sprite->setFlipX(true);
	this->SetLocation(this->GetLocation() + Vec2(-this->speed, 0));
}

void CCharacter::MoveRight()
{
	this->sprite->setFlipX(false);
	this->SetLocation(this->GetLocation() + Vec2(this->speed, 0));
}

void CCharacter::Jump()
{

}