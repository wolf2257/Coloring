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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(CGameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	

	auto sprite = Sprite::create("gamescene/background/3.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto sprite1 = Sprite::create("gamescene/character/char.png");
	sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto tb = CBrickTable::Create(18, 10, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 14, 1);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 15, 1);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 16, 1);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 0, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 1, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 2, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 3, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 4, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 5, 2);

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
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 10, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 11, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 12, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 13, 7);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 17, 7);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 10, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 11, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 12, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 13, 8);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 17, 8);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 2, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 3, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 4, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 5, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 6, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 7, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 8, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 10, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 11, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 12, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 13, 9);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 17, 9);

	this->addChild(sprite, 0);
	this->addChild(sprite1, 2);
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
