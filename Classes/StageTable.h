#ifndef __CStageTable_H__
#define __CStageTable_H__

#include "cocos2d.h"
#include "Character.h"
#include "Brick.h"
#include "Bullet.h"

class CStageTable
{
private:
	CStageTable();
	std::list<CBrick*> table;
	std::list<CBrick*> bullets;
	CCharacter* Character;
	cocos2d::Vec2 Brick00Pos;
	int rows, cols;
	int currentColor;
	bool IsMoveablePlace(std::list<CBrick*>);
	bool IsHangablePlace(std::list<CBrick*>);
public:
	static CStageTable* Create(int, int, cocos2d::Vec2 = cocos2d::Vec2(0,0));
	~CStageTable();

	void Add(CBrick* brick, cocos2d::Vec2 position);
	std::list<CBrick*> GetBricks(cocos2d::Vec2 position);
	void RemoveBrick(cocos2d::Vec2 position);

	bool AddCharacter(cocos2d::Vec2 position);
	CCharacter* GetCharacter();
	bool RemoveCharacter();

	void Update(float ut);
	void AttatchAll(cocos2d::Layer*, int);

	static cocos2d::Vec2 BrickSize;
	cocos2d::Vec2 GetBrickLocation(cocos2d::Vec2 position);
	cocos2d::Vec2 AdjustObjPos(cocos2d::Vec2 location);

	enum CharAction { MoveLeft, MoveRight, MoveUp, MoveDown };
	void MoveCharacter(CharAction Act);
	int Coloring();
	void VerficationBrickVisibleState(int color);
};

#endif