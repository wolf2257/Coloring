#ifndef __CCharacter_H__
#define __CCharacter_H__

#include "GameObject.h"

class CCharacter : public CGameObject
{
private:
	CCharacter();
public:
	static CCharacter* Create(cocos2d::Vec2 = cocos2d::Vec2(0, 0));
	~CCharacter();

	void MoveLeft();
	void MoveRight();
	void Jump();
};

#endif