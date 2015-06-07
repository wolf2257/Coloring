#include "BrickTable.h"
#include "ColoringPallet.h"

using namespace std;
USING_NS_CC;

Vec2 CBrickTable::BrickSize = Vec2(50, 50);

CBrickTable::CBrickTable()
{
}


CBrickTable::~CBrickTable()
{
}


CBrickTable* CBrickTable::Create(int rows, int cols, Vec2 Axis)
{
	auto Table = new CBrickTable();

	Table->rows = rows;
	Table->cols = cols;

	// Array allocation
	//Table->table = new CBrick**[cols];
	//for (int i = 0; i < cols; ++i) {
	//	Table->table[i] = new CBrick*[rows];
	//	memset(Table->table[i], 0, sizeof(int)*rows);
	//}

	Table->Brick00Pos = Vec2(Axis.x - rows * BrickSize.x / 2 + BrickSize.x / 2, Axis.y + cols * BrickSize.y / 2 - BrickSize.y / 2);

	return Table;
}

void CBrickTable::Add(CBrick* brick, Vec2 position)
{
	brick->SetPosition(position);
	brick->SetLocation(GetBrickLocation(position));
	table.push_back(brick);
}

std::list<CBrick*>  CBrickTable::GetBricks(Vec2 position)
{
	auto list = std::list<CBrick*>();
	for (auto itr = table.begin(); itr != table.end(); ++itr) {
		auto itrPos = (*itr)->GetPosition();
		if (itrPos.x == position.x && itrPos.y == position.y)
		{
			list.push_back(*itr);
		}
	}

	return list;
}

void CBrickTable::RemoveBrick(Vec2 position)
{
	for each (auto var in GetBricks(position))
	{
		table.remove(var);
	}
}

bool CBrickTable::AddCharacter(Vec2 position)
{
	this->Character = CCharacter::Create(GetBrickLocation(position));
	this->Character->SetPosition(position);
	return true;
}

CCharacter* CBrickTable::GetCharacter()
{
	return this->Character;
}

bool CBrickTable::RemoveCharacter()
{
	return false;
}

Vec2 CBrickTable::GetBrickLocation(Vec2 position)
{
	return Vec2(
		Brick00Pos.x + position.x * BrickSize.x,
		Brick00Pos.y - position.y * BrickSize.y);
}

void CBrickTable::AttatchAll(Layer* layer, int zOrder)
{
	for (auto itr = table.begin(); itr != table.end(); ++itr) {
		(*itr)->Attatch(layer, zOrder);
	}
	Character->Attatch(layer, zOrder);
}

void CBrickTable::Update(float ut)
{
	this->Character->SetPosition(AdjustObjPos(this->Character->GetLocation()));
	this->Character->Update(ut);
	if (this->Character->jumpCount > 0 && !this->Character->hanging)
	{
		if (IsMoveablePlace(GetBricks(Character->GetPosition() + Vec2(0, -1))))
		{
			this->Character->JumpTick();
		}
		else
		{
			this->Character->jumpCount = 0;
			this->Character->jumping = false;
		}
	}
	else if (!this->Character->hanging &&
		IsMoveablePlace(GetBricks(Character->GetPosition() + Vec2(0, 1))))
	{
		this->Character->SetLocation(this->Character->GetLocation() - Vec2(0, this->Character->GetSpeed()));
	}
	else
	{
		this->Character->jumping = false;
	}
}

void CBrickTable::MoveCharacter(CBrickTable::CharAction direction)
{
	switch (direction)
	{
	case CBrickTable::MoveLeft:
		if (IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() + Vec2(Character->GetSize().width / 2, 0)) + Vec2(-1, 0))))
		{
			this->Character->MoveLeft();
		}
		break;
	case CBrickTable::MoveRight:
		if (IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(1, 0))))
		{
			this->Character->MoveRight();
		}
		break;
	case CBrickTable::MoveUp:
		if (IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(0, -1))))
		{
			this->Character->MoveUp();
		}
		break;
	case CBrickTable::MoveDown:
		if (IsMoveablePlace(GetBricks(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(0, 1))))
		{
			this->Character->MoveDown();
		}
		break;
	default:
		break;
	}
}

bool CBrickTable::IsMoveablePlace(std::list<CBrick*>  brick)
{
	if (Character->hanging)
	{
		if (brick.size() == 0)
		{
			Character->hanging = false;
			return false;
		}
		for each (auto var in brick)
		{
			switch (var->Type)
			{
			case CBrick::BrickType::Rope:
			case CBrick::BrickType::RopeHead:
				continue;
			default:
				return false;
			}
		}
	}
	else if (brick.size() > 0)
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
				continue;
			default:
				return false;
			}
		}
	}

	return true;
}

Vec2 CBrickTable::AdjustObjPos(Vec2 location)
{
	return Vec2(
		round((location.x - Brick00Pos.x) / BrickSize.x),
		round((Brick00Pos.y - location.y) / BrickSize.y)
		);
}

int CBrickTable::Coloring()
{
	for each (auto var in this->GetBricks(this->GetCharacter()->GetPosition()))
	{
		if (var != nullptr)
		{
			switch (var->Type)
			{
			case CBrick::BrickType::AuraRed:
				return 1;
				break;
			case CBrick::BrickType::AuraGreen:
				return 2;
				break;
			case CBrick::BrickType::AuraYellow:
				return 3;
				break;
			}
		}
	}

}