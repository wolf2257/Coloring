#ifndef __ColoringPallet__H__
#define __ColoringPallet__H__

#include "cocos2d.h"
#include "GameObject.h"


class CColoringPallet : public CGameObject
{
public:
private:
	CColoringPallet();
	static cocos2d::Map<char*, cocos2d::Texture2D*> pallet;
	Pallets color;
public:
	static CColoringPallet* Create(cocos2d::Vec2);
	~CColoringPallet();

	void Coloring(Pallets);
	cocos2d::Rect GetBound();
};

#endif