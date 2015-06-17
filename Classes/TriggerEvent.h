#ifndef __Trigger_EVENT_H__
#define __Trigger_EVENT_H__

#include "cocos2d.h"
#include "GameObject.h"
class CTriggerCause
{
private:
	CTriggerCause();
public:
	static CTriggerCause* Create();
	~CTriggerCause();

	CGameObject *obj;
	cocos2d::Vec2 location;
};

class CTriggerEffect
{
private:
	CTriggerEffect();
public:
	static CTriggerEffect* Create();
	~CTriggerEffect();
};
#endif