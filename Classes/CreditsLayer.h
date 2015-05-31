#ifndef __CREDITS_LAYER_H__
#define __CREDITS_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class CCreditsLayer : public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(CCreditsLayer);
	virtual bool init();
	void UpButtonCallback(cocos2d::Ref* pSender);
	void MoveLayersToDown(float f);
};

#endif