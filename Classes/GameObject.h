#ifndef __CGameObject_H__
#define __CGameObject_H__

#include "cocos2d.h"
class CGameObject
{
protected:
	CGameObject();
	cocos2d::Sprite *sprite;
	float speed;
	cocos2d::Vec2 position;
public:
	~CGameObject();
	void Attatch(cocos2d::Layer*, int);

	// Properties
	inline void SetPosition(cocos2d::Vec2 position) { this->position = position; }
	inline cocos2d::Vec2 GetPosition() { return position; }
	inline cocos2d::Vec2 GetLocation() { return sprite->getPosition(); }
	inline void SetLocation(cocos2d::Vec2 location) { this->sprite->setPosition(location); }
	inline cocos2d::Size GetSize() { return sprite->getContentSize(); }
	inline void SetSize(cocos2d::Size location) { this->sprite->setContentSize(location); }
	inline float GetSpeed() { return speed; }
	inline void SetSpeed(float speed) { this->speed = speed; }
};

#endif