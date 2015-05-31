#ifndef __LEVEL_DECIDE_B_LAYER_H__
#define __LEVEL_DECIDE_B_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class CLevelDecideB : public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(CLevelDecideB);
	virtual bool init();

	void DownButtonCallback(cocos2d::Ref* pSender);
	void MoveLayersToUp(float f);
};

#endif