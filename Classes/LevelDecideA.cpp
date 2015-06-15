#include "LevelDecideA.h"
#include "MenuScene.h"
#include "DecideHolder.h"

bool CLevelDecideA::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("backgrounds/black.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite);

	auto closeItem = MenuItemImage::create(
		"buttons/down.png",
		"buttons/down.png",
		CC_CALLBACK_1(CLevelDecideA::DownButtonCallback, this));

	closeItem->setPosition(Vec2(closeItem->getContentSize().width / 2 + 5, visibleSize.height - closeItem->getContentSize().height / 2 - 5));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto tb = CDecideHolder::Create(4, 1, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	tb->AddBrick(CLevelButton::Create(CLevelButton::ButtonType::A1), 0, 0);
	tb->AddBrick(CLevelButton::Create(CLevelButton::ButtonType::A2), 1, 0);
	tb->AddBrick(CLevelButton::Create(CLevelButton::ButtonType::A3), 2, 0);
	tb->AddBrick(CLevelButton::Create(CLevelButton::ButtonType::A4), 3, 0);

	//tb->GetBrick(0, 0)->GetSprite()->schedule 
	tb->AttatchAll(this, 1);

	return true;
}

void CLevelDecideA::DownButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CLevelDecideA::MoveLayersToUp), 0);
}

void CLevelDecideA::MoveLayersToUp(float f)
{
	CMenuScene::SharedInstance->runAction(CCMoveBy::create(0.5, Vec2(0, CMenuScene::SharedInstance->visibleSize.height)));
}

void CLevelDecideA::UpButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CCreditsLayer::MoveLayersToDown), 0);
}

void CLevelDecideA::MoveLayersToDown(float f)
{
	CMenuScene::SharedInstance->runAction(CCMoveBy::create(0.5, Vec2(0, -CMenuScene::SharedInstance->visibleSize.height)));
}