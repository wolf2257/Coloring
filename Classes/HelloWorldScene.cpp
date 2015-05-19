#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	

	auto sprite = Sprite::create("gamescene/background/3.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto tb = CBrickTable::Create(5, 3, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 0, 0);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 1, 0);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 2, 0);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 3, 0);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Glass), 4, 0);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 1);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 1);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 2, 1);

	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 0, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 1, 2);
	tb->AddBrick(CBrick::Create(CBrick::BrickType::Empty), 2, 2);
	
	this->addChild(sprite, 0);
	tb->AttatchAll(this, 1);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
