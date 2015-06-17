#ifndef __Trigger_H__
#define __Trigger_H__

#include "TriggerEvent.h"
#include "cocos2d.h"
class CTrigger
{
private:
	CTrigger();
public:
	static CTrigger* Create(CTriggerCause *tc, CTriggerEffect *te);
	~CTrigger();

	void Update(float dt);
};

#endif