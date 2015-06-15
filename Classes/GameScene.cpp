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

	visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	isResultDroped = false;
	isEnded = false;

	resultLayer = CGameResultLayer::create();
	resultLayer->setPosition(Vec2(0, visibleSize.height));
	this->addChild(resultLayer, CGameObject::LayerZOrders::UI + 1);

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

	m2lFlag = m2rFlag = m2uFlag = false;

	const int margin = 10;

	LeftButton = Sprite::create("buttons/left.png");
	LeftButton->setPosition(Vec2(LeftButton->getContentSize().width / 2 + margin, LeftButton->getContentSize().height / 2 + margin));
	this->addChild(LeftButton, 4);

	RightButton = Sprite::create("buttons/right.png");
	RightButton->setPosition(Vec2((LeftButton->getContentSize().width * 1.7) + margin, LeftButton->getContentSize().height / 2 + margin));
	this->addChild(RightButton, 4);

	JumpButton = Sprite::create("buttons/jump.png");
	JumpButton->setPosition(Vec2(visibleSize.width - LeftButton->getContentSize().width / 2 - margin, LeftButton->getContentSize().height / 2 + margin));
	this->addChild(JumpButton, 4);


#ifdef _DEBUG

	auto closeItem = MenuItemImage::create(
		"closenormal.png",
		"closeselected.png",
		CC_CALLBACK_1(CGameScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(CGameScene::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(CGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

#endif

	tb = CStageTable::Create(this, 18, 10, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	tb->AddCharacter(Vec2(2, 7));

	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(14, 1));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(15, 1));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(16, 1));

	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(0, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(1, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(2, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(3, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(4, 2));

	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(0, 3));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(1, 3));

	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(0, 4));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(1, 4));

	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(0, 5));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(1, 5));

	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(0, 6));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(1, 6));
	tb->Add(CBrick::Create(CBrick::BrickType::Basket, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(17, 6));

	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(0, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(1, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(10, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(11, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(12, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(13, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::WaterHead, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(14, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::WaterHead, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(15, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::WaterHead, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(16, 7));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(17, 7));

	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(0, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(1, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(10, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(11, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(12, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(13, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::Water, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(14, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::Water, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(15, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::Water, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(16, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(17, 8));

	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(0, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(1, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(2, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(3, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(4, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(5, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(6, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(7, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::GlassGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(8, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(10, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(11, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(12, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(13, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::Water, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(14, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::Water, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(15, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::Water, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(16, 9));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(17, 9));

	tb->Add(CBrick::Create(CBrick::BrickType::TreeRed, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(1, 1));
	tb->Add(CBrick::Create(CBrick::BrickType::AuraRed, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(1, 1));

	tb->Add(CBrick::Create(CBrick::BrickType::TreeGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(11, 6));
	tb->Add(CBrick::Create(CBrick::BrickType::AuraGreen, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(11, 6));

	tb->Add(CBrick::Create(CBrick::BrickType::RopeHead, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(4, 1));
	tb->Add(CBrick::Create(CBrick::BrickType::Rope, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(4, 2));
	tb->Add(CBrick::Create(CBrick::BrickType::Rope, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(4, 3));
	tb->Add(CBrick::Create(CBrick::BrickType::Rope, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(4, 4));
	tb->Add(CBrick::Create(CBrick::BrickType::Rope, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(4, 5));
	tb->Add(CBrick::Create(CBrick::BrickType::Rope, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(4, 6));
	tb->Add(CBrick::Create(CBrick::BrickType::Rope, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(4, 7));

	tb->Add(CBrick::Create(CBrick::BrickType::Log, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(16, 0));
	tb->Add(CBrick::Create(CBrick::BrickType::Invisible, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(14, 0));
	tb->Add(CBrick::Create(CBrick::BrickType::Invisible, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::GameObjects), Vec2(16, 0));

	tb->Add(CBrick::Create(CBrick::BrickType::GlassRed, CGameObject::Pallets::Red, CGameObject::LayerZOrders::Terrians), Vec2(9, 8));
	tb->Add(CBrick::Create(CBrick::BrickType::EmptyGround, CGameObject::Pallets::Red, CGameObject::LayerZOrders::Terrians), Vec2(9, 9));

	tb->SetEndpoint(Vec2(17, 6));
	//tb->AttatchAll();


	cp = CColoringPallet::Create(Vec2(visibleSize.width - (LeftButton->getContentSize().width * 1.7) - margin, LeftButton->getContentSize().height / 2 + margin));
	tb->Coloring(CGameObject::Pallets::Empty);
	cp->Coloring(CGameObject::Pallets::Empty);
	cp->Attatch(this, 5);
	return true;
}


void CGameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void CGameScene::update(float dt)
{
	switch (tb->IsEnd())
	{
	case CStageTable::StageState::Cleared:
		ShowResult();
		break;
	case CStageTable::StageState::Dead:
		ShowResult();
		break;
	default:
		if (m2lFlag)
		{
			tb->MoveCharacter(CStageTable::CharAction::MoveLeft);
		}
		else if (m2rFlag)
		{
			tb->MoveCharacter(CStageTable::CharAction::MoveRight);
		}
		else if (m2uFlag)
		{
			tb->MoveCharacter(CStageTable::CharAction::MoveUp);
		}
		break;
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
		if (tb->GetCharacter()->JumpStatus == CCharacter::Idle)
		{
			if (!isEnded)
				tb->Jump();
		}
		else if (tb->GetCharacter()->JumpStatus == CCharacter::Jumping || tb->GetCharacter()->JumpStatus == CCharacter::Hanging)
		{
			m2uFlag = true;
		}
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
	if (LeftButton->boundingBox().containsPoint(point))
	{
		m2lFlag = false;
	}
	else if (RightButton->boundingBox().containsPoint(point))
	{
		m2rFlag = false;
	}
	else if (JumpButton->boundingBox().containsPoint(point))
	{
		m2uFlag = false;
	}
}

Sprite* CGameScene::GenBackground()
{
	switch (rand() % 4)
	{
	default:
		return Sprite::create("backgrounds/orange.png");
	case 1:
		return Sprite::create("backgrounds/rink.png");
	case 2:
		return Sprite::create("backgrounds/blue.png");
	case 3:
		return Sprite::create("backgrounds/mint.png");
	}
}

void CGameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		m2lFlag = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		m2rFlag = true;
		break;
	case EventKeyboard::KeyCode::KEY_ALT:
		if (tb->GetCharacter()->JumpStatus == CCharacter::Idle)
		{
			if (!isEnded)
			tb->Jump();
		}
		else if (tb->GetCharacter()->JumpStatus == CCharacter::Jumping || tb->GetCharacter()->JumpStatus == CCharacter::Hanging)
		{
			m2uFlag = true;
		}
		break;
	case EventKeyboard::KeyCode::KEY_CTRL:
		this->cp->Coloring((CColoringPallet::Pallets)tb->Coloring());
		break;
	case EventKeyboard::KeyCode::KEY_1:
		this->tb->Coloring(CGameObject::Pallets::Yellow);
		this->cp->Coloring(CGameObject::Pallets::Yellow);
		break;
	}
}

void CGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		m2lFlag = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		m2rFlag = false;
		break;
	case EventKeyboard::KeyCode::KEY_ALT:
		m2uFlag = false;
		break;
	}
}

void CGameScene::ShowResult()
{
	if (isResultDroped == false)
	{
		resultLayer->runAction(CCMoveTo::create(0.5, Vec2(0, 0)));
		isResultDroped = true;
		CCLOG("%d", tb->GetProcessTime()/1000);
	}
}