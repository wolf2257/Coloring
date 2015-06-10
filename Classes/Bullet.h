#ifndef __BULLET_H__
#define __BULLET_H__

#include "GameObject.h"
#include "cocos2d.h"
class CBullet :
	public CGameObject
{
private:
	CBullet();
	Direction direction;
public:
	static CBullet* Create(Direction dir, cocos2d::Vec2 = cocos2d::Vec2(0, 0));
	~CBullet();

	void Update(float dt);
};

#endif