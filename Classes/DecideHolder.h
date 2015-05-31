#ifndef __CDecideHolder_H__
#define __CDecideHolder_H__

#include "LevelButton.h"

class CDecideHolder
{
private:
	CDecideHolder();
	CLevelButton*** table;
	cocos2d::Vec2 Brick00Pos;
	int rows, cols;
public:
	static CDecideHolder* Create(int, int, cocos2d::Vec2 = cocos2d::Vec2(0, 0));
	~CDecideHolder();

	bool AddBrick(CLevelButton* brick, int row, int col);
	CLevelButton* GetBrick(int row, int col);
	bool RemoveBrick(int row, int col);

	void AttatchAll(cocos2d::Layer*, int);

	static cocos2d::Vec2 BrickSize;
	cocos2d::Vec2 GetBrickLocation(int row, int col);
};

#endif