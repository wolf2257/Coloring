#include "BackgroundLayer.h"
#include "MenuScene.h"

CBackgroundLayer* CBackgroundLayer::SharedInstance;
bool CBackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	creditLayer = CCreditsLayer::create();
	levelLayerA = CLevelDecideA::create();
	creditLayer->setPosition(Vec2(0, -visibleSize.height));
	levelLayerA->setPosition(Vec2(0, visibleSize.height));
	this->addChild(creditLayer);
	this->addChild(levelLayerA);
	auto cover = Sprite::create("backgrounds/cover.png");
	cover->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0));
	cover->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(cover);


	auto title = Sprite::create("title.png");
	title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.width * 2.25 / 5));
	this->addChild(title);

	soundItem = MenuItemImage::create(
		"buttons/sound_on.png",
		"buttons/sound_on_2.png",
		CC_CALLBACK_1(CBackgroundLayer::menuSoundCallback, this));
	soundItem->setPosition(Vec2(-(visibleSize.width * 1 / 3.5), 0));

	auto startItem = MenuItemImage::create(
		"buttons/start.png",
		"buttons/start_2.png",
		CC_CALLBACK_1(CBackgroundLayer::DownButtonCallback, this));
	startItem->setPosition(Vec2(0, 0));

	auto creditItem = MenuItemImage::create(
		"buttons/credit.png",
		"buttons/credit_2.png",
		CC_CALLBACK_1(CBackgroundLayer::UpButtonCallback, this));
	creditItem->setPosition(Vec2(visibleSize.width * 1 / 3.5, 0));

	auto menu = Menu::create(soundItem, startItem, creditItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 1 / 6));
	this->addChild(menu);
	return true;
}

void CBackgroundLayer::menuSoundCallback(cocos2d::Ref* pSender)
{

}

void CBackgroundLayer::DownButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CBackgroundLayer::MoveLayersToDown), 0);
}

void CBackgroundLayer::UpButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CBackgroundLayer::MoveLayersToUp), 0);
}

void CBackgroundLayer::MoveLayersToUp(float f)
{
	SharedInstance->runAction(EaseInOut::create(CCMoveBy::create(0.5, Vec2(0, visibleSize.height)), 4.0));
}

void CBackgroundLayer::MoveLayersToDown(float f)
{
	SharedInstance->runAction(EaseInOut::create(CCMoveBy::create(0.5, Vec2(0, -visibleSize.height)), 4.0));
}