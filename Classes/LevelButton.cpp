#include "LevelButton.h"

USING_NS_CC;

CLevelButton::CLevelButton()
{
}


CLevelButton::~CLevelButton()
{
}

CLevelButton* CLevelButton::Create(ButtonType type, Vec2 location)
{
	auto path = "Decide/"; 
	auto Brick = new CLevelButton();
	switch (type)
	{
	case CLevelButton::Lock:
		Brick->sprite = Sprite::create(
			"Decide/Lock.png"
			);
		break;
	case CLevelButton::A1:
		Brick->sprite = Sprite::create(
			"Decide/A/1.png"
			);
		break;
	case CLevelButton::A2:
		Brick->sprite = Sprite::create(
			"Decide/A/2.png"
			);
		break;
	case CLevelButton::A3:
		Brick->sprite = Sprite::create(
			"Decide/A/3.png"
			);
		break;
	case CLevelButton::A4:
		Brick->sprite = Sprite::create(
			"Decide/A/4.png"
			);
		break;
	case CLevelButton::B1:
		Brick->sprite = Sprite::create(
			"Decide/B/1.png"
			);
		break;
	case CLevelButton::B2:
		Brick->sprite = Sprite::create(
			"Decide/B/2.png"
			);
		break;
	default:
		//return nullptr;
		break;
	}
	Brick->sprite->setPosition(location);
	return Brick;
}

void CLevelButton::Attatch(Layer *layer, int zOrder)
{
	layer->addChild(this->sprite, zOrder);
}