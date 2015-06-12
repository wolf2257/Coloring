#ifndef __GameResult_LAYER_H__
#define __GameResult_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class CGameResultLayer : public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(CGameResultLayer);
	virtual bool init();
	void UpButtonCallback(cocos2d::Ref* pSender);
	void MoveLayersToDown(float f);
};

#endif