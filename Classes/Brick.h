#ifndef __CBrick_H__
#define __CBrick_H__

#include "cocos2d.h"

class CBrick
{
public:
	enum BrickType { Empty, Glass };
private:
	CBrick();
	cocos2d::Sprite *sprite;
public:
	static CBrick* Create(BrickType, cocos2d::Vec2 = cocos2d::Vec2(0, 0));
	~CBrick();
	void CBrick::Attatch(cocos2d::Layer*, int);

	// Properties
	inline cocos2d::Vec2 GetLocation() { return sprite->getPosition(); }
	inline void SetLocation(cocos2d::Vec2 location) { this->sprite->setPosition(location); }
	inline cocos2d::Size GetSize() { return sprite->getContentSize(); }
	inline void SetSize(cocos2d::Size location) { this->sprite->setContentSize(location); }

};

#endif