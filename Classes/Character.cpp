#include "Character.h"

USING_NS_CC;
cocos2d::Map<char*, cocos2d::Texture2D*> CCharacter::animations;

CCharacter::CCharacter()
{
	animations.insert("Stand", Director::getInstance()->getTextureCache()->addImage("Charactor/Stand.png"));
	animations.insert("Walk1", Director::getInstance()->getTextureCache()->addImage("Charactor/Walk1.png"));
	animations.insert("Walk2", Director::getInstance()->getTextureCache()->addImage("Charactor/Walk2.png"));
}


CCharacter::~CCharacter()
{
}

CCharacter* CCharacter::Create(Vec2 location)
{
	auto chara = new CCharacter();
	chara->sprite = Sprite::createWithTexture(animations.at("Stand"));
	chara->sprite->setPosition(location);
	chara->sprite->setAnchorPoint(Vec2(0.5, 0.7));
	chara->SetSpeed(3);
	chara->AnimCount = 0;
	chara->AnimStopCount = 0;
	chara->AnimStatus = Stand;
	return chara;
}


void CCharacter::MoveLeft()
{
	this->filp = true;
	this->sprite->setFlipX(true);
	this->SetLocation(this->GetLocation() + Vec2(-this->speed, 0));
	if (AnimCount++ > 10)
	{
		switch (AnimStatus)
		{
		case CCharacter::Stand:
		case CCharacter::Walk2:
			this->sprite->setTexture(animations.at("Walk1"));
			AnimStatus = Walk1;
			break;
		case CCharacter::Walk1:
			this->sprite->setTexture(animations.at("Walk2"));
			AnimStatus = Walk2;
			break;
		}
		AnimCount = 0;
	}
	AnimStopCount = 0;
}

void CCharacter::MoveRight()
{
	this->filp = false;
	this->sprite->setFlipX(false);
	this->SetLocation(this->GetLocation() + Vec2(this->speed, 0));
	if (AnimCount++ > 10)
	{
		switch (AnimStatus)
		{
		case CCharacter::Stand:
		case CCharacter::Walk2:
			this->sprite->setTexture(animations.at("Walk1"));
			AnimStatus = Walk1;
			break;
		case CCharacter::Walk1:
			this->sprite->setTexture(animations.at("Walk2"));
			AnimStatus = Walk2;
			break;
		}
		AnimCount = 0;
	}
	AnimStopCount = 0;
}

void CCharacter::Jump()
{

}

void CCharacter::Update(float dt)
{
	if (AnimStopCount++ > 10)
	{
		this->sprite->setTexture(animations.at("Stand"));
		AnimStatus = CCharacter::AnimationStatus::Stand;
	}
}