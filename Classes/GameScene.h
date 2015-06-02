#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Brick.h"
#include "BrickTable.h"
#include "Character.h"
#include "Stage.h"

class CGameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    
    // implement the "static create()" method manually
	CREATE_FUNC(CGameScene);

	virtual void update(float dt);

private:
	cocos2d::Sprite *LeftButton, *RightButton;
	CBrickTable *tb;


	bool m2lFlag, m2rFlag;
};

#endif // __HELLOWORLD_SCENE_H__
