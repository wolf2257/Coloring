#include "MenuScene.h"
#include "GameScene.h"
Scene* CMenuScene::scene()
{
	Scene *scene = Scene::create();
	CMenuScene *layer = CMenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool CMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	creditLayer = CCreditsLayer::create();
	levelLayerA = CLevelDecideA::create();
	levelLayerB = CLevelDecideB::create();
	this->addChild(creditLayer);
	this->addChild(levelLayerA);
	this->addChild(levelLayerB);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	soundItem = MenuItemImage::create(
		"Buttons/Sound_On.png",
		"Buttons/Sound_On_2.png",
		CC_CALLBACK_1(CMenuScene::menuSoundCallback, this));
	soundItem->setPosition(Vec2(-(visibleSize.width * 1 / 4), 0));

	auto startItem = MenuItemImage::create(
		"Buttons/Start.png",
		"Buttons/Start_2.png",
		CC_CALLBACK_1(CMenuScene::menuStartCallback, this));
	startItem->setPosition(Vec2(0, 0));

	auto creditItem = MenuItemImage::create(
		"Buttons/Credit.png",
		"Buttons/Credit_2.png",
		CC_CALLBACK_1(CMenuScene::menuCreditsCallback, this));
	creditItem->setPosition(Vec2(visibleSize.width * 1 / 4, 0));

	auto menu = Menu::create(soundItem, startItem, creditItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 1/ 4));
	this->addChild(menu);
	return true;
}

void CMenuScene::menuSoundCallback(cocos2d::Ref* pSender)
{
	
}

void CMenuScene::menuStartCallback(cocos2d::Ref* pSender)
{
	Scene *pScene = TransitionCrossFade::create(3.0, CGameScene::createScene());
	Director::getInstance()->replaceScene(pScene);
}

void CMenuScene::menuCreditsCallback(cocos2d::Ref* pSender)
{

}