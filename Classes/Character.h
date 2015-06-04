#ifndef __CCharacter_H__
#define __CCharacter_H__

#include "GameObject.h"
#include "cocos2d.h"

class CCharacter : public CGameObject
{
private:
	CCharacter();
	static cocos2d::Map<char*, cocos2d::Texture2D*> animations;

	int AnimCount;
	int AnimStopCount;
	enum AnimationStatus { Stand, Walk1, Walk2 } AnimStatus;
public:
	static CCharacter* Create(cocos2d::Vec2 = cocos2d::Vec2(0, 0));
	~CCharacter();

	void Update(float dt);

	void MoveLeft();
	void MoveRight();
	void Jump();
};

#endif