#include "LevelDecideB.h"
#include "MenuScene.h"

bool CLevelDecideB::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("backgrounds/credit.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite);

	auto closeItem = MenuItemImage::create(
		"buttons/down.png",
		"buttons/down.png",
		CC_CALLBACK_1(CLevelDecideB::DownButtonCallback, this));

	closeItem->setPosition(Vec2(closeItem->getContentSize().width / 2 + 5, visibleSize.height - closeItem->getContentSize().height / 2 - 5));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void CLevelDecideB::DownButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CLevelDecideB::MoveLayersToUp), 0);
}

void CLevelDecideB::MoveLayersToUp(float f)
{
	CMenuScene::SharedInstance->runAction(CCMoveBy::create(0.5, Vec2(0, CMenuScene::SharedInstance->visibleSize.height)));
}
