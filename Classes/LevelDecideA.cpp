#include "LevelDecideA.h"
#include "BackgroundLayer.h"
#include "GameScene.h"
bool CLevelDecideA::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setTouchEnabled(true);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listner = EventListenerTouchOneByOne::create();
	listner->setSwallowTouches(false);
	listner->onTouchBegan = CC_CALLBACK_2(CLevelDecideA::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(CLevelDecideA::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listner, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"buttons/down.png",
		"buttons/down.png",
		CC_CALLBACK_1(CLevelDecideA::DownButtonCallback, this));

	closeItem->setPosition(Vec2(closeItem->getContentSize().width / 2 + 5, visibleSize.height - closeItem->getContentSize().height / 2 - 5));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	tb = CDecideHolder::Create(4, 1, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	tb->AddBrick(CLevelButton::Create(CLevelButton::ButtonType::B1), 0, 0);
	tb->AddBrick(CLevelButton::Create(CLevelButton::ButtonType::Lock), 1, 0);
	tb->AddBrick(CLevelButton::Create(CLevelButton::ButtonType::Lock), 2, 0);
	tb->AddBrick(CLevelButton::Create(CLevelButton::ButtonType::Lock), 3, 0);

	tb->AttatchAll(this, 1);

	return true;
}

void CLevelDecideA::DownButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CLevelDecideA::MoveLayersToUp), 0);
}

void CLevelDecideA::MoveLayersToUp(float f)
{
	CBackgroundLayer::SharedInstance->runAction(EaseInOut::create(CCMoveBy::create(0.5, Vec2(0, CBackgroundLayer::SharedInstance->visibleSize.height)), 3.5));
}

void CLevelDecideA::UpButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CCreditsLayer::MoveLayersToDown), 0);
}

void CLevelDecideA::MoveLayersToDown(float f)
{
	CBackgroundLayer::SharedInstance->runAction(EaseInOut::create(CCMoveBy::create(0.5, Vec2(0, -CBackgroundLayer::SharedInstance->visibleSize.height)), 3.5));
}

bool CLevelDecideA::onTouchBegan(Touch* touch, Event* event)
{
	auto point = touch->getLocation();
	if (tb->GetBrick(0, 0)->GetSprite()->boundingBox().containsPoint(point))
	{
		Director::getInstance()->replaceScene(CGameScene::createScene());
	}
	return true;
}

void CLevelDecideA::onTouchEnded(Touch* touch, Event* event)
{
	auto point = touch->getLocation();
}
