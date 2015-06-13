#ifndef __CGameObject_H__
#define __CGameObject_H__

#include "cocos2d.h"
class CGameObject
{
public:	
	enum Pallets { Empty, Red, Green, Yellow };
	enum Direction { Left, Right };
	enum LayerZOrders {Background, Terrians, GameObjects, PlayerObjects,Player, UI};
	enum BrickType {
		Air, Invisible,
		EmptyGround, GlassGreen, GlassRed, WaterHead, Water,
		RopeHead, Rope,
		Log, Basket,
		TreeRed, TreeGreen, TreeYellow,
		AuraRed, AuraGreen, AuraYellow
	}
	Type;

protected:
	CGameObject();
	cocos2d::Sprite *sprite;
	float speed;
	cocos2d::Vec2 position;
	bool filp;
	bool visible;
	Pallets RevelationColor; //발현색
	int zOrder;
	std::list<cocos2d::Vec2> AdditionalLocation;
public:
	~CGameObject();
	void Attatch(cocos2d::Layer*, int, int=0);

	bool isGraviry; //중력 작용 여부
	bool isDestroy; //파괴 가능 여부
	virtual void Update(float dt);
	void VerficationVisibleState(Pallets currentColoring);

	inline void Release() {
		sprite->release();
	}
	inline cocos2d::Sprite* getSprite() { return sprite; }

	inline void SetAdditional(cocos2d::Vec2 pos) { AdditionalLocation.push_back(pos); }
	inline std::list<cocos2d::Vec2> GetAdditional() {return AdditionalLocation; }

	// Properties
	inline void Show() { this->sprite->setOpacity(255); visible = true; }
	inline void Hide() { this->sprite->setOpacity(50); visible = false; }
	inline void SetPosition(cocos2d::Vec2 position) { this->position = position; }
	inline cocos2d::Vec2 GetPosition() {  return  position; }
	inline cocos2d::Vec2 GetLocation() { return sprite->getPosition(); }
	inline void SetLocation(cocos2d::Vec2 location) { this->sprite->setPosition(location); }
	inline cocos2d::Size GetSize() { return sprite->getContentSize(); }
	inline void SetSize(cocos2d::Size location) { this->sprite->setContentSize(location); }
	inline float GetSpeed() { return speed; }
	inline void SetSpeed(float speed) { this->speed = speed; }
	inline bool GetVisible() { return visible; }
	inline int GetZorder() { return zOrder; }
	inline Direction GetDirection() { return (filp == true) ? Direction::Left : Direction::Right; }

};

#endif