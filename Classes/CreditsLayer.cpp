#include "CreditsLayer.h"
#include "MenuScene.h"

bool CCreditsLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("Backgrounds/Credit.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite);

	auto closeItem = MenuItemImage::create(
		"Buttons/Up.png",
		"Buttons/Up.png",
		CC_CALLBACK_1(CCreditsLayer::UpButtonCallback, this));

	closeItem->setPosition(Vec2(closeItem->getContentSize().width / 2 + 5, visibleSize.height - closeItem->getContentSize().height / 2 - 5));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void CCreditsLayer::UpButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CCreditsLayer::MoveLayersToDown), 0);
}

void CCreditsLayer::MoveLayersToDown(float f)
{
	CMenuScene::SharedInstance->runAction(CCMoveBy::create(0.5, Vec2(0, -CMenuScene::SharedInstance->visibleSize.height)));
}