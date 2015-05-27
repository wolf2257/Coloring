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

	void menuSoundCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuCreditsCallback(cocos2d::Ref* pSender);
private:
	CCreditsLayer *creditLayer;
	CLevelDecideA *levelLayerA;
	CLevelDecideB *levelLayerB;

	cocos2d::MenuItem *soundItem;
};

#endif