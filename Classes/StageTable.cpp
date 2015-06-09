#include "StageTable.h"
#include "ColoringPallet.h"

using namespace std;
USING_NS_CC;

Vec2 CStageTable::BrickSize = Vec2(50, 50);

CStageTable::CStageTable()
{
}


CStageTable::~CStageTable()
{
}


CStageTable* CStageTable::Create(int rows, int cols, Vec2 Axis)
{
	auto Table = new CStageTable();

	Table->rows = rows;
	Table->cols = cols;
	Table->currentColor = 0;

	// Array allocation
	//Table->table = new CBrick**[cols];
	//for (int i = 0; i < cols; ++i) {
	//	Table->table[i] = new CBrick*[rows];
	//	memset(Table->table[i], 0, sizeof(int)*rows);
	//}

	Table->Brick00Pos = Vec2(Axis.x - rows * BrickSize.x / 2 + BrickSize.x / 2, Axis.y + cols * BrickSize.y / 2 - BrickSize.y / 2);

	return Table;
}

void CStageTable::Add(CBrick* brick, Vec2 position)
{
	brick->SetPosition(position);
	brick->SetLocation(GetBrickLocation(position));
	table.push_back(brick);
}

std::list<CBrick*>  CStageTable::GetBricks(Vec2 position)
{
	auto list = std::list<CBrick*>();
	for (auto itr = table.begin(); itr != table.end(); ++itr) {
		auto itrPos = (*itr)->GetPosition();
		if (itrPos.x == position.x && itrPos.y == position.y && (*itr)->GetVisible() == true)
		{
			list.push_back(*itr);
		}
	}

	return list;
}

void CStageTable::RemoveBrick(Vec2 position)
{
	for each (auto var in GetBricks(position))
	{
		table.remove(var);
	}
}

bool CStageTable::AddCharacter(Vec2 position)
{
	this->Character = CCharacter::Create(GetBrickLocation(position));
	this->Character->SetPosition(position);
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

void CStageTable::AttatchAll(Layer* layer, int zOrder)
{
	for (auto itr = table.begin(); itr != table.end(); ++itr) {
		(*itr)->Attatch(layer, zOrder);
	}
	Character->Attatch(layer, zOrder);
	this->VerficationBrickVisibleState(0);
}

void CStageTable::Update(float ut)
{
	this->Character->SetPosition(AdjustObjPos(this->Character->GetLocation()));
	this->Character->Update(ut);

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
		if (   IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(1, 0))) &&
			   (!Character->Remaining || IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(1, 1))))   )
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

bool CStageTable::IsMoveablePlace(std::list<CBrick*>  brick)
{
	if (brick.size() > 0)
	{
		for each (auto var in brick)
		{
			switch (var->Type)
			{
			case CBrick::BrickType::AuraRed:
			case CBrick::BrickType::AuraGreen:
			case CBrick::BrickType::AuraYellow:
			case CBrick::BrickType::TreeRed:
			case CBrick::BrickType::TreeGreen:
			case CBrick::BrickType::TreeYellow:
			case CBrick::BrickType::Rope:
			case CBrick::BrickType::RopeHead:
			case CBrick::BrickType::Water:
			case CBrick::BrickType::WaterHead:
				continue;
			default:
				return false;
			}
		}
	}

	return true;
}

bool CStageTable::IsHangablePlace(std::list<CBrick*>  brick)
{
	if (Character->JumpStatus == Character->Jumping)
	{
		if (brick.size() == 0)
		{
			return false;
		}
		for each (auto var in brick)
		{
			switch (var->Type)
			{
			case CBrick::BrickType::Rope:
			case CBrick::BrickType::RopeHead:
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
		for each (auto var in brick)
		{
			switch (var->Type)
			{
			case CBrick::BrickType::Rope:
			case CBrick::BrickType::RopeHead:
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
	int color = -1;
	for each (auto var in this->GetBricks(this->GetCharacter()->GetPosition()))
	{
		if (var != nullptr)
		{
			switch (var->Type)
			{
			case CBrick::BrickType::AuraRed:
				if (currentColor == 0)
					currentColor = 1;
				else
					currentColor = 3;
				break;
			case CBrick::BrickType::AuraGreen:
				if (currentColor == 2)
					currentColor = 1;
				else
					currentColor = 3;
				break;
			case CBrick::BrickType::AuraYellow:
				currentColor = 3;
				break;
			default:
				currentColor = 0;
				break;
			}
		}
	}

	VerficationBrickVisibleState(currentColor);
	return currentColor;

}

void CStageTable::VerficationBrickVisibleState(int color)
{
	for each (auto var in table)
	{
		var->VerficationVisibleState((CGameObject::Pallets)color);
	}
}