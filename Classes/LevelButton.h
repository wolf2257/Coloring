#ifndef __CLevelButton_H__
#define __CLevelButton_H__

#include "cocos2d.h"

class CLevelButton
{
public:
	enum ButtonType { 
		Lock,
		A1, A2, A3, A4,
		B1, B2
	};
private:
	CLevelButton();
	cocos2d::Sprite *sprite;
public:
	static CLevelButton* Create(ButtonType, cocos2d::Vec2 = cocos2d::Vec2(0, 0));
	~CLevelButton();
	void CLevelButton::Attatch(cocos2d::Layer*, int);

	// Properties
	inline cocos2d::Vec2 GetLocation() { return sprite->getPosition(); }
	inline void SetLocation(cocos2d::Vec2 location) { this->sprite->setPosition(location); }
	inline cocos2d::Size GetSize() { return sprite->getContentSize(); }
	inline void SetSize(cocos2d::Size location) { this->sprite->setContentSize(location); }
	inline cocos2d::Sprite* GetSprite() { return sprite; }

};

#endif