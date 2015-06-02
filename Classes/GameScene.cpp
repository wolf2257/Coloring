#include "GameScene.h"

USING_NS_CC;

Scene* CGameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	this->setTouchEnabled(true);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listner = EventListenerTouchOneByOne::create();
	listner->setSwallowTouches(false);
	listner->onTouchBegan = CC_CALLBACK_2(CGameScene::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(CGameScene::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listner, this);

	auto bg = Sprite::create("Backgrounds/Black.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	auto LeftButton = Sprite::create("Buttons/Left.png");
	LeftButton->setPosition(Vec2(LeftButton->getContentSize().width / 2 + 5, LeftButton->getContentSize().height / 2 + 5));
	this->addChild(LeftButton, 2);

	auto RightButton = Sprite::create("Buttons/Right.png");
	RightButton->setPosition(Vec2((LeftButton->getContentSize().width * 1.7) + 5, LeftButton->getContentSize().height / 2 + 5));
	this->addChild(RightButton, 2);


#ifdef _DEBUG

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CGameScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

#endif
	
	tb = CBrickTable::Create(18, 10, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	tb->AddCharacter(0,1);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 14, 1);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 15, 1);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 16, 1);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 0, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 1, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 2, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 3, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 4, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 5, 2);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 3);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 3);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 4);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 4);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 5);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 5);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 6);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 6);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 10, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 11, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 12, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 13, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 17, 7);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 10, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 11, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 12, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 13, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 17, 8);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 2, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 3, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 4, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 5, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 6, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 7, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::GlassGreen), 8, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 10, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 11, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 12, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 13, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 17, 9);

	tb->AttatchAll(this, 1);

	return true;
}


void CGameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void CGameScene::update(float dt) {
	if (!m2lFlag || !m2rFlag)
	{
		if (m2lFlag)
		{
			tb->GetCharacter()->MoveLeft();
		}
		else if (m2rFlag)
		{
			tb->GetCharacter()->MoveRight();
		}
	}
	tb->Update(dt);
}


bool CGameScene::onTouchBegan(Touch* touch, Event* event)
{
	auto point = touch->getLocation();

	if (LeftButton->boundingBox().containsPoint(point))
	{
		m2lFlag = true;
	}
	else if (RightButton->boundingBox().containsPoint(point))
	{
		m2rFlag = true;
	}
	return true;
}

void CGameScene::onTouchEnded(Touch* touch, Event* event)
{
	auto point = touch->getLocation();
	auto lb = LeftButton->boundingBox();
	auto db = RightButton->boundingBox();
	if (lb.containsPoint(point))
	{
		m2lFlag = false;
	}
	else if (db.containsPoint(point))
	{
		m2rFlag = false;
	}
}