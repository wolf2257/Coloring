#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "CreditsLayer.h"
#include "LevelDecideA.h"
#include "LevelDecideB.h"

USING_NS_CC;

class CMenuScene : public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(CMenuScene);
	virtual bool init();

	static CMenuScene *SharedInstance;

	Size visibleSize;
	Vec2 origin;
private:

	CCreditsLayer *creditLayer;
	CLevelDecideA *levelLayerA;
	CLevelDecideB *levelLayerB;

	cocos2d::MenuItem *soundItem;
	enum BackgroundType { Black, Blue, Mint, Orange, Pink };
	std::string BackgroundDecider(int index);

	void menuSoundCallback(cocos2d::Ref* pSender);
	void UpButtonCallback(cocos2d::Ref* pSender);
	void DownButtonCallback(cocos2d::Ref* pSender);
	
	void MoveLayersToUp(float f);
	void MoveLayersToDown(float f);
};

#endif