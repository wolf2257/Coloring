#include "MenuScene.h"

using namespace std;

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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	background = CBackgroundLayer::create();
	CBackgroundLayer::SharedInstance = background;
	this->addChild(background, 1);

	auto background = Sprite::create("backgrounds/mint.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);

	
	return true;
}