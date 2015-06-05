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

	auto bg = GenBackground();
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	m2lFlag = m2rFlag = false;

	const int margin = 10;

	LeftButton = Sprite::create("Buttons/Left.png");
	LeftButton->setPosition(Vec2(LeftButton->getContentSize().width / 2 + margin, LeftButton->getContentSize().height / 2 + margin));
	this->addChild(LeftButton, 4);

	RightButton = Sprite::create("Buttons/Right.png");
	RightButton->setPosition(Vec2((LeftButton->getContentSize().width * 1.7) + margin, LeftButton->getContentSize().height / 2 + margin));
	this->addChild(RightButton, 4);

	JumpButton = Sprite::create("Buttons/Jump.png");
	JumpButton->setPosition(Vec2(visibleSize.width - LeftButton->getContentSize().width / 2 - margin, LeftButton->getContentSize().height / 2 + margin));
	this->addChild(JumpButton, 4);

	cp = CColoringPallet::Create(Vec2(visibleSize.width - (LeftButton->getContentSize().width * 1.7) - margin, LeftButton->getContentSize().height / 2 + margin));
	cp->Coloring(CColoringPallet::Pallets::Empty);
	cp->Attatch(this, 5);

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
	tb->AddCharacter(Vec2(2,7));

#ifndef Terrians  
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(14, 1));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(15, 1));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(16, 1));
		   
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(0, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(1, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(2, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(3, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(4, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(5, 2));
		   
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(0, 3));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(1, 3));
		   
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(0, 4));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(1, 4));
		   
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(0, 5));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(1, 5));
		   
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(0, 6));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(1, 6));
		   
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(0, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(1, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(10, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(11, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(12, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(13, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(17, 7));
		   
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(0, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(1, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(10, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(11, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(12, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(13, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(17, 8));
		   
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(0, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(1, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(2, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(3, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(4, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(5, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(6, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(7, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen), Vec2(8, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(10, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(11, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(12, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(13, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround), Vec2(17, 9));
#endif

#ifndef Trees
	tb->Add(CBrick::Create(CBrick::BrickType::TreeRed), Vec2(1, 1));
	tb->Add(CBrick::Create(CBrick::BrickType::Invisible), Vec2(1, 0));

	tb->Add(CBrick::Create(CBrick::BrickType::TreeGreen), Vec2(11, 6));
	tb->Add(CBrick::Create(CBrick::BrickType::Invisible), Vec2(11, 5));
#endif

	tb->Add(CBrick::Create(CBrick::BrickType::RedAura), Vec2(5, 8));

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
			tb->MoveCharacter(CBrickTable::CharAction::MoveLeft);
		}
		else if (m2rFlag)
		{
			tb->MoveCharacter(CBrickTable::CharAction::MoveRight);
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
	else if (JumpButton->boundingBox().containsPoint(point))
	{
		
	}
	else if (cp->GetBound().containsPoint(point))
	{
		this->cp->Coloring((CColoringPallet::Pallets)tb->Coloring());
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

Sprite* CGameScene::GenBackground()
{
	switch (rand() % 4)
	{
	default:
		return Sprite::create("Backgrounds/Orange.png");
	case 1:
		return Sprite::create("Backgrounds/Pink.png");
	case 2:
		return Sprite::create("Backgrounds/Blue.png");
	case 3:
		return Sprite::create("Backgrounds/Mint.png");
	}
}