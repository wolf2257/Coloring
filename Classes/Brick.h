#ifndef __CBrick_H__
#define __CBrick_H__

#include "GameObject.h"

class CBrick : public CGameObject
{
public:
	enum BrickType { EmptyGround, GlassGreen, GlassRed, Invisible, TreeRed, TreeGreen, RedAura } Type;
private:
	CBrick();
public:
	static CBrick* Create(BrickType, cocos2d::Vec2 = cocos2d::Vec2(0, 0));
	~CBrick();
};

#endif