#include "GameObject.h"

USING_NS_CC;

CGameObject::CGameObject()
{
	visible = true;
	filp = false;
}


CGameObject::~CGameObject()
{
}

void CGameObject::Attatch(Layer *layer, int zOrder)
{
	layer->addChild(this->sprite, zOrder);
}