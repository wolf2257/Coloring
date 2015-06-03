#ifndef __CBrickTable_H__
#define __CBrickTable_H__

#include "cocos2d.h"
#include "Brick.h"
#include "Character.h"
class CBrickTable
{
private:
	CBrickTable();
	std::list<CBrick*> table;
	CCharacter* Character;
	cocos2d::Vec2 Brick00Pos;
	int rows, cols;
public:
	static CBrickTable* Create(int, int, cocos2d::Vec2 = cocos2d::Vec2(0,0));
	~CBrickTable();

	void AddBrick(CBrick* brick, cocos2d::Vec2 position);
	CBrick* GetBrick(cocos2d::Vec2 position);
	void RemoveBrick(cocos2d::Vec2 position);

	bool AddCharacter(cocos2d::Vec2 position);
	CCharacter* GetCharacter();
	bool RemoveCharacter();

	void Update(float ut);
	void AttatchAll(cocos2d::Layer*, int);

	static cocos2d::Vec2 BrickSize;
	cocos2d::Vec2 GetBrickLocation(cocos2d::Vec2 position);
	cocos2d::Vec2 AdjustObjPos(cocos2d::Vec2 location);
};

#endif