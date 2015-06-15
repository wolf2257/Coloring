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
	auto Brick = new CLevelButton();
	switch (type)
	{
	case CLevelButton::Lock:
		Brick->sprite = Sprite::create(
			"decide/lock.png"
			);
		break;
	case CLevelButton::A1:
		Brick->sprite = Sprite::create(
			"decide/a/1.png"
			);
		break;
	case CLevelButton::A2:
		Brick->sprite = Sprite::create(
			"decide/a/2.png"
			);
		break;
	case CLevelButton::A3:
		Brick->sprite = Sprite::create(
			"decide/a/3.png"
			);
		break;
	case CLevelButton::A4:
		Brick->sprite = Sprite::create(
			"decide/a/4.png"
			);
		break;
	case CLevelButton::B1:
		Brick->sprite = Sprite::create(
			"decide/b/1.png"
			);
		break;
	case CLevelButton::B2:
		Brick->sprite = Sprite::create(
			"decide/b/2.png"
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