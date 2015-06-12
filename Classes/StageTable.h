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
	std::list<CGameObject*> table;
	std::list<CBullet*> bullets;
	CCharacter* Character;
	cocos2d::Vec2 Brick00Pos;
	int rows, cols;
	CGameObject::Pallets currentColor;
	bool IsMoveablePlace(std::list<CGameObject*>);
	bool IsMoveablePlace(CGameObject*);
	bool IsHangablePlace(std::list<CGameObject*>);
	cocos2d::Layer* layer;
	cocos2d::Rect VisibleSize;
	cocos2d::Vec2 EndPoint;
	bool StageEnd;

	void WorldsEnd();
	void DeleteObject(CGameObject* object);
public:
	static CStageTable* Create(cocos2d::Layer*, int, int, cocos2d::Vec2 = cocos2d::Vec2(0, 0));
	~CStageTable();

	void Add(CGameObject* brick, cocos2d::Vec2 position);
	std::list<CGameObject*> GetBricks(cocos2d::Vec2 position);
	void RemoveBrick(cocos2d::Vec2 position);

	bool AddCharacter(cocos2d::Vec2 position);
	CCharacter* GetCharacter();
	bool RemoveCharacter();

	void SetEndpoint(cocos2d::Vec2 position) { EndPoint = position; }
	cocos2d::Vec2 GetEndpoint() { return EndPoint; }

	void Update(float ut);
	void AttatchAll();

	static cocos2d::Vec2 BrickSize;
	cocos2d::Vec2 GetBrickLocation(cocos2d::Vec2 position);
	cocos2d::Vec2 AdjustObjPos(cocos2d::Vec2 location);

	enum CharAction { MoveLeft, MoveRight, MoveUp, MoveDown };
	void MoveCharacter(CharAction Act);
	int Coloring();
	void Coloring(CGameObject::Pallets i);
	void VerficationBrickVisibleState(int color);
	void LaunchBullet();


	bool IsEnd(){
		return StageEnd;
	}
};

#endif