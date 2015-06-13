#include "GameObject.h"

USING_NS_CC;

CGameObject::CGameObject()
{
	visible = true;
	filp = false;
	speed = 3;
	isDestroy = false;
	isGraviry = false;
	Type = BrickType::Invisible;
}


CGameObject::~CGameObject()
{
}

void CGameObject::Attatch(Layer *layer, int zOrder, int tag)
{
	layer->addChild(this->sprite, zOrder, tag);
}

void CGameObject::Update(float dt)
{

}


void CGameObject::VerficationVisibleState(Pallets currentColoring)
{
	if (this->RevelationColor == Pallets::Empty) return;

	if (this->RevelationColor == currentColoring)
	{
		this->Show();
	}
	else
	{
		this->Hide();
	}

}