#pragma once
#include "cocos2d.h"
#include "Brick.h"
class CBrickTable
{
private:
	CBrickTable();
	CBrick*** table;
	cocos2d::Vec2 Brick00Pos;
	int rows, cols;
public:
	static CBrickTable* Create(int, int, cocos2d::Vec2 = cocos2d::Vec2(0,0));
	~CBrickTable();

	bool AddBrick(CBrick* brick, int row, int col);
	CBrick* GetBrick(int row, int col);
	bool RemoveBrick(int row, int col);

	void AttatchAll(cocos2d::Layer*, int);

	static cocos2d::Vec2 BrickSize;
	cocos2d::Vec2 GetBrickLocation(int row, int col);
};