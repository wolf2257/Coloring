#include "ColoringPallet.h"

USING_NS_CC;
Map<char*, cocos2d::Texture2D*> CColoringPallet::pallet;

CColoringPallet::CColoringPallet()
{
	pallet.insert("Invisible", Director::getInstance()->getTextureCache()->addImage("Buttons/Pallets/Invisible.png"));
	pallet.insert("Red", Director::getInstance()->getTextureCache()->addImage("Buttons/Pallets/Red.png"));
	pallet.insert("Green", Director::getInstance()->getTextureCache()->addImage("Buttons/Pallets/Green.png"));
	pallet.insert("Yellow", Director::getInstance()->getTextureCache()->addImage("Buttons/Pallets/Yellow.png"));
}


CColoringPallet::~CColoringPallet()
{

}

CColoringPallet* CColoringPallet::Create(cocos2d::Vec2 location)
{
	auto Brick = new CColoringPallet();
	Brick->sprite = Sprite::createWithTexture(pallet.at("Invisible"));
	Brick->sprite->setPosition(location);
	Brick->color = CColoringPallet::Pallets::Empty;
	return Brick;
}

void CColoringPallet::Coloring(Pallets color)
{
	switch (color)
	{
	case CColoringPallet::Empty:
		this->sprite->setTexture(pallet.at("Invisible"));
		break;
	case CColoringPallet::Red:
		this->sprite->setTexture(pallet.at("Red"));
		break;
	case CColoringPallet::Yellow:
		this->sprite->setTexture(pallet.at("Yellow"));
		break;
	case CColoringPallet::Green:
		this->sprite->setTexture(pallet.at("Green"));
		break;
	default:
		break;
	}
}


Rect CColoringPallet::GetBound()
{
	return this->sprite->getBoundingBox();
}