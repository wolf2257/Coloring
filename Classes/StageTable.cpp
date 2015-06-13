#include "StageTable.h"
#include "ColoringPallet.h"

using namespace std;
USING_NS_CC;

Vec2 CStageTable::BrickSize = Vec2(50, 50);

CStageTable::CStageTable()
{
	StageEnd = Playing;
	au_1 = false;
	tick_inited = GetTime();
}


CStageTable::~CStageTable()
{
}


CStageTable* CStageTable::Create(cocos2d::Layer* layer, int rows, int cols, Vec2 Axis)
{
	auto Table = new CStageTable();

	Table->layer = layer;
	Table->rows = rows;
	Table->cols = cols;
	Table->currentColor = CGameObject::Pallets::Empty;
	auto vs = layer->getContentSize();
	Table->VisibleSize = Rect(0, 0, vs.width, vs.height);;
	// Array allocation
	//Table->table = new CGameObject**[cols];
	//for (int i = 0; i < cols; ++i) {
	//	Table->table[i] = new CGameObject*[rows];
	//	memset(Table->table[i], 0, sizeof(int)*rows);
	//}

	Table->Brick00Pos = Vec2(Axis.x - rows * BrickSize.x / 2 + BrickSize.x / 2, Axis.y + cols * BrickSize.y / 2 - BrickSize.y / 2);

	return Table;
}

void CStageTable::Add(CGameObject* brick, Vec2 position)
{
	brick->SetPosition(position);
	brick->SetLocation(GetBrickLocation(position));
	table.push_back(brick);
	brick->Attatch(layer, brick->GetZorder());
}

std::list<CGameObject*>  CStageTable::GetBricks(Vec2 position)
{
	auto list = std::list<CGameObject*>();
	for (auto itr = table.begin(); itr != table.end(); ++itr) {
		auto itrPos = (*itr)->GetPosition();
		if (itrPos.x == position.x && itrPos.y == position.y && (*itr)->GetVisible() == true && (*itr)->Type != CGameObject::BrickType::Air)
		{
			list.push_back(*itr);
		}
	}

	return list;
}

void CStageTable::RemoveBrick(Vec2 position)
{
	for (auto var : GetBricks(position))
	{
		table.remove(var);
	}
}

bool CStageTable::AddCharacter(Vec2 position)
{
	this->Character = CCharacter::Create(GetBrickLocation(position));
	this->Character->SetPosition(position);
	table.push_back(this->Character);
	Character->Attatch(layer, Character->GetZorder());
	return true;
}

CCharacter* CStageTable::GetCharacter()
{
	return this->Character;
}

bool CStageTable::RemoveCharacter()
{
	return false;
}

Vec2 CStageTable::GetBrickLocation(Vec2 position)
{
	return Vec2(
		Brick00Pos.x + position.x * BrickSize.x,
		Brick00Pos.y - position.y * BrickSize.y);
}

void CStageTable::AttatchAll()
{
	for (auto itr = table.begin(); itr != table.end(); ++itr) {
		(*itr)->Attatch(layer, (*itr)->GetZorder());
	}
	this->VerficationBrickVisibleState(0);
}

void CStageTable::Update(float ut)
{
	// Endpoint
	if (Character->GetPosition() == EndPoint)
	{
		WorldsEnd();
	}

	// Objects Process
	for (auto var : table)
	{
		var->Update(ut);
		var->SetPosition(AdjustObjPos(var->GetLocation()));
		if (var->isGraviry)
		{
			if (IsMoveablePlace(GetBricks(var->GetPosition() + Vec2(0, 1))))
			{
				var->SetLocation(var->GetLocation() - Vec2(0, var->GetSpeed()));
			}
		}
	}

	// 탄환 CC
	for (auto var = bullets.begin(); var != bullets.end();)
	{
		bool isBulletDeleted = false;
		(*var)->SetPosition(AdjustObjPos((*var)->GetLocation()));
		auto bricks = GetBricks((*var)->GetPosition() + Vec2(0, 0));
		for (auto brick = bricks.begin(); brick != bricks.end(); brick++)
		{
			// 벼ㄱ에 닿으면 총알 파괴
			if (!IsMoveablePlace((*brick)))
			{
				// 벽의 파괴 가능 여부 확
				if ((*brick)->isDestroy)
				{
					auto p = *brick;
					for (auto b = table.begin(); b != table.end(); b++)
					{
						if ((*b) == p)
						{
							table.erase(b);
							break;
						}
					}
					DeleteObject(p);
				}

				auto p2 = *var;
				bullets.erase(var++);
				DeleteObject(p2);
				isBulletDeleted = true;
				break;
			}
			else
			{
			}
		}
		if (isBulletDeleted)
		{
			continue;
		}

		if (!VisibleSize.containsPoint((*var)->GetLocation()))
		{
			auto pointer = *var;
			bullets.erase(var++);
			DeleteObject(pointer);
		}
		else
		{
			var++;
		}
	}

	// 점프
	if (Character->JumpStatus == Character->Jumping)
	{
		// 위에 블록 없음
		if (IsMoveablePlace(GetBricks(Character->GetPosition() + Vec2(0, -1))))
		{
			this->Character->JumpTick();
		}
		// 위에 블록 있음
		else
		{
			this->Character->jumpCount = 0;
			Character->JumpStatus = Character->Idle;
		}
	}
	// 사다리에 매달림
	else if (Character->JumpStatus == Character->Hanging)
	{
	}
	// 중력
	else if (IsMoveablePlace(GetBricks(Character->GetPosition() + Vec2(0, 1))))
	{
		this->Character->SetLocation(this->Character->GetLocation() - Vec2(0, this->Character->GetSpeed()));
		Character->Remaining = true;
	}
	else
	{
		Character->JumpStatus = Character->Idle;
		Character->Remaining = false;
	}
	for(auto var : bullets)
	{
		var->Update(ut);
	}


#ifndef 임시
	if (!au_1)
	{

		auto au = GetBricks(Vec2(16, 7));
		for (auto var : au)
		{
			if (var->Type == CGameObject::BrickType::Log)
			{
				this->Add(CBrick::Create(CBrick::BrickType::Invisible, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(14, 7));
				this->Add(CBrick::Create(CBrick::BrickType::Invisible, CGameObject::Pallets::Empty, CGameObject::LayerZOrders::Terrians), Vec2(15, 7));
				au_1 = true;
			}
		}
	}

	auto bs = GetBricks(Character->GetPosition() + Vec2(0, 1));
	for (auto var : bs)
	{
		if (var->Type == CGameObject::BrickType::Water)
		{
			Die();
		}
	}

#endif

	if (!VisibleSize.containsPoint(Character->GetLocation()))
	{
		Die();
	}
}

void CStageTable::MoveCharacter(CStageTable::CharAction direction)
{
	switch (direction)
	{
	case CStageTable::MoveLeft:
		if (Character->JumpStatus != CCharacter::Hanging)
		if (IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() + Vec2(Character->GetSize().width / 2, 0)) + Vec2(-1, 0))) &&
			(!Character->Remaining || IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(-1, 1)))))
		{
			this->Character->MoveLeft();
		}
		break;
	case CStageTable::MoveRight:
		if (Character->JumpStatus != CCharacter::Hanging)
		if (IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(1, 0))) &&
			(!Character->Remaining || IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(1, 1)))))
		{
			this->Character->MoveRight();
		}
		break;
	case CStageTable::MoveUp:
		if (IsHangablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(0, 0))))
		{
			this->Character->MoveUp();
		}
		break;
	case CStageTable::MoveDown:
		if (IsHangablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(0, 1))))
		{
			this->Character->MoveDown();
		}
		break;
	default:
		break;
	}
}

bool CStageTable::IsMoveablePlace(CGameObject*  brick)
{
	switch (brick->Type)
	{
	case CGameObject::BrickType::Air:
	case CGameObject::BrickType::AuraRed:
	case CGameObject::BrickType::AuraGreen:
	case CGameObject::BrickType::AuraYellow:
	case CGameObject::BrickType::TreeRed:
	case CGameObject::BrickType::TreeGreen:
	case CGameObject::BrickType::TreeYellow:
	case CGameObject::BrickType::Rope:
	case CGameObject::BrickType::RopeHead:
	case CGameObject::BrickType::WaterHead:
	case CGameObject::BrickType::Basket :
		return true;
	default:
		return false;
	}
}

bool CStageTable::IsMoveablePlace(std::list<CGameObject*>  bricks)
{
	if (bricks.size() > 0)
	{

		for (auto var : bricks)
		{
			if (IsMoveablePlace(var)) continue;
			else return false;
		}
	}

	return true;
}

bool CStageTable::IsHangablePlace(std::list<CGameObject*>  brick)
{
	if (Character->JumpStatus == Character->Jumping)
	{
		if (brick.size() == 0)
		{
			return false;
		}
		for (auto var : brick)
		{
			switch (var->Type)
			{
			case CGameObject::BrickType::Rope:
			case CGameObject::BrickType::RopeHead:
				Character->JumpStatus = Character->Hanging;
				return true;
			default:
				continue;
			}
		}
	}
	// 매달린 상태
	else if (Character->JumpStatus == Character->Hanging)
	{
		if (brick.size() == 0)
		{
			Character->JumpStatus = Character->End;
			return true;
		}
		for (auto var : brick)
		{
			switch (var->Type)
			{
			case CGameObject::BrickType::Rope:
			case CGameObject::BrickType::RopeHead:
				return true;
			default:
				continue;
			}
		}
	}

	return false;
}

Vec2 CStageTable::AdjustObjPos(Vec2 location)
{
	return Vec2(
		round((location.x - Brick00Pos.x) / BrickSize.x),
		round((Brick00Pos.y - location.y) / BrickSize.y)
		);
}

int CStageTable::Coloring()
{
	CGameObject::Pallets color = CGameObject::Pallets::Empty;
	bool ctr = true;
	for (auto var : this->GetBricks(this->GetCharacter()->GetPosition()))
	{
		if (var != nullptr)
		{
			switch (var->Type)
			{
			case CGameObject::BrickType::AuraRed:
				if (currentColor == CGameObject::Pallets::Green)
				{
					currentColor = CGameObject::Pallets::Yellow;
				}
				else
				{
					currentColor = CGameObject::Pallets::Red;
				}
				ctr = false;
				break;

			case CGameObject::BrickType::AuraGreen:
				if (currentColor == CGameObject::Pallets::Red)
				{

					currentColor = CGameObject::Pallets::Yellow;
				}
				else
				{
					currentColor = CGameObject::Pallets::Green;
				}
				ctr = false;
				break;

			case CGameObject::BrickType::AuraYellow:
				currentColor = CGameObject::Pallets::Yellow;
				ctr = false;
				break;
			}
		}
	}


	if (ctr)
	{
		if (currentColor == CGameObject::Pallets::Yellow)
		{
			LaunchBullet();
		}
		currentColor = CGameObject::Pallets::Empty;
	}

	Coloring(currentColor);
	return currentColor;

}

void CStageTable::Coloring(CGameObject::Pallets i)
{
	currentColor = i;
	VerficationBrickVisibleState(currentColor);
}

void CStageTable::VerficationBrickVisibleState(int color)
{
	for (auto var : table)
	{
		var->VerficationVisibleState((CGameObject::Pallets)color);
	}
}

void CStageTable::LaunchBullet()
{
	auto launcher = CBullet::Create(Character->GetDirection(), Character->GetLocation() -  Vec2(0, 30));
	launcher->Attatch(layer, launcher->GetZorder());
	bullets.push_back(launcher);
}

void CStageTable::DeleteObject(CGameObject* object)
{
	layer->removeChild(object->getSprite(), true);
	delete object;
}

void CStageTable::WorldsEnd()
{
	StageEnd = Cleared;
	tick_ended = GetTime();
}

void CStageTable::Jump()
{
	if (!Character->Remaining) Character->Jump();
}

void CStageTable::Die()
{
	StageEnd = Dead;
	tick_ended = GetTime();
}

unsigned int CStageTable::GetTime()
{
	timeval getTick;
	cocos2d::gettimeofday(&getTick, 0);
	return getTick.tv_sec * 1000 + getTick.tv_usec / 1000;
}