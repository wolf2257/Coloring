#ifndef __CGameObject_H__
#define __CGameObject_H__

#include "cocos2d.h"
class CGameObject
{
protected:
	CGameObject();
	cocos2d::Sprite *sprite;
	float speed;
	int row, col;
public:
	~CGameObject();
	void Attatch(cocos2d::Layer*, int);

	// Properties
	inline void SetPosition(int row, int col) { this->row = row; this->col = col; }
	inline int GetRow() { return row; }
	inline int GetCol() { return col; }
	inline cocos2d::Vec2 GetLocation() { return sprite->getPosition(); }
	inline void SetLocation(cocos2d::Vec2 location) { this->sprite->setPosition(location); }
	inline cocos2d::Size GetSize() { return sprite->getContentSize(); }
	inline void SetSize(cocos2d::Size location) { this->sprite->setContentSize(location); }
	inline float GetSpeed() { return speed; }
	inline void SetSpeed(float speed) { this->speed = speed; }
};

#endif