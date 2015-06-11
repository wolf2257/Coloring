#ifndef __CBrick_H__
#define __CBrick_H__

#include "GameObject.h"

class CBrick : public CGameObject
{
private:
	CBrick();
public:
	static CBrick* Create(BrickType, CGameObject::Pallets, LayerZOrders);
	~CBrick();
};

#endif