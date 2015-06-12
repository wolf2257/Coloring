#include "GameResultLayer.h"

bool CGameResultLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("result.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite);
	return true;
}

void CGameResultLayer::UpButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CGameResultLayer::MoveLayersToDown), 0);
}

void CGameResultLayer::MoveLayersToDown(float f)
{
}