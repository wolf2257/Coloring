#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include "CreditsLayer.h"
#include "LevelDecideA.h"
USING_NS_CC;

class CBackgroundLayer : public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(CBackgroundLayer);
	virtual bool init();


	CCreditsLayer *creditLayer;
	CLevelDecideA *levelLayerA;

	static CBackgroundLayer *SharedInstance;

	Size visibleSize;
	Vec2 origin;

	cocos2d::MenuItem *soundItem;
	void menuSoundCallback(cocos2d::Ref* pSender);
	void UpButtonCallback(cocos2d::Ref* pSender);
	void DownButtonCallback(cocos2d::Ref* pSender);

	void MoveLayersToUp(float f);
	void MoveLayersToDown(float f);
};

#endif