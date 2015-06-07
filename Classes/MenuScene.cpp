#include "MenuScene.h"

using namespace std;
CMenuScene* CMenuScene::SharedInstance;

Scene* CMenuScene::scene()
{
	Scene *scene = Scene::create();
	CMenuScene *layer = CMenuScene::create();
	SharedInstance = layer;
	scene->addChild(layer);

	return scene;
}

bool CMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin		= Director::getInstance()->getVisibleOrigin();

	creditLayer = CCreditsLayer::create();
	levelLayerA = CLevelDecideA::create();
	levelLayerB = CLevelDecideB::create();
	creditLayer->setPosition(Vec2(0, -visibleSize.height));
	levelLayerA->setPosition(Vec2(0, visibleSize.height));
	levelLayerB->setPosition(Vec2(0, visibleSize.height * 2));
	this->addChild(creditLayer);
	this->addChild(levelLayerA);
	this->addChild(levelLayerB);

	auto background = Sprite::create(BackgroundDecider(rand() % 5));
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	auto cover = Sprite::create("Backgrounds/Title.png");
	cover->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	cover->setAnchorPoint(Vec2(0.5,0.8));
	this->addChild(cover);

	soundItem = MenuItemImage::create(
		"Buttons/Sound_On.png",
		"Buttons/Sound_On_2.png",
		CC_CALLBACK_1(CMenuScene::menuSoundCallback, this));
	soundItem->setPosition(Vec2(-(visibleSize.width * 1 / 4), 0));

	auto startItem = MenuItemImage::create(
		"Buttons/Start.png",
		"Buttons/Start_2.png",
		CC_CALLBACK_1(CMenuScene::DownButtonCallback, this));
	startItem->setPosition(Vec2(0, 0));

	auto creditItem = MenuItemImage::create(
		"Buttons/Credit.png",
		"Buttons/Credit_2.png",
		CC_CALLBACK_1(CMenuScene::UpButtonCallback, this));
	creditItem->setPosition(Vec2(visibleSize.width * 1 / 4, 0));

	auto menu = Menu::create(soundItem, startItem, creditItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 1 / 4));
	this->addChild(menu);
	return true;
}

void CMenuScene::menuSoundCallback(cocos2d::Ref* pSender)
{

}

void CMenuScene::DownButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CMenuScene::MoveLayersToDown), 0);
}

void CMenuScene::UpButtonCallback(cocos2d::Ref* pSender)
{
	scheduleOnce(schedule_selector(CMenuScene::MoveLayersToUp), 0);
}


string CMenuScene::BackgroundDecider(int index)
{
	string path = "Backgrounds/";
	switch (index)
	{
	case BackgroundType::Black:
		path += "Black.png";
		break;
	case BackgroundType::Blue:
		path += "Blue.png";
		break;
	case BackgroundType::Mint:
		path += "Mint.png";
		break;
	case BackgroundType::Orange:
		path += "Orange.png";
		break;
	case BackgroundType::Pink:
		path += "Pink.png";
		break;
	default:
		path += "FUCKYOU^^";
	}

	return path;
}


void CMenuScene::MoveLayersToUp(float f)
{
	SharedInstance->runAction(CCMoveBy::create(0.5, Vec2(0, visibleSize.height)));
}

void CMenuScene::MoveLayersToDown(float f)
{
	SharedInstance->runAction(CCMoveBy::create(0.5, Vec2(0, -visibleSize.height)));
}