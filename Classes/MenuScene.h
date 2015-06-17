#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"

USING_NS_CC;

class CMenuScene : public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(CMenuScene);
	virtual bool init();
private:

	CBackgroundLayer *background;
};

#endif