#ifndef __LEVEL_DECIDE_A_LAYER_H__
#define __LEVEL_DECIDE_A_LAYER_H__

#include "DecideHolder.h"
#include "cocos2d.h"
USING_NS_CC;

class CLevelDecideA : public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(CLevelDecideA);
	virtual bool init();

	void DownButtonCallback(cocos2d::Ref* pSender);
	void MoveLayersToUp(float f);
	void UpButtonCallback(cocos2d::Ref* pSender);
	void MoveLayersToDown(float f);

	CDecideHolder *tb;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif