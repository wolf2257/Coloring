#include "BrickTable.h"
#include "ColoringPallet.h"

using namespace std;
USING_NS_CC;

Vec2 CBrickTable::BrickSize = Vec2(45, 45);

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

CBrick* CBrickTable::GetBrick(Vec2 position)
{
	for (auto itr = table.begin(); itr != table.end(); ++itr) {
		auto itrPos = (*itr)->GetPosition();
		if (itrPos.x == position.x && itrPos.y == position.y)
		{
			return *itr;
		}
	}
	return nullptr;
}

void CBrickTable::RemoveBrick(Vec2 position)
{
	table.remove(GetBrick(position));
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
	if (GetBrick(Character->GetPosition() + Vec2(0, 1)) == nullptr)
	{
		this->Character->SetLocation(this->Character->GetLocation() - Vec2(0, this->Character->GetSpeed()));
	}
}

void CBrickTable::MoveCharacter(CBrickTable::CharAction direction)
{
	switch (direction)
	{
	case CBrickTable::MoveLeft:
		if (IsMoveablePlace(GetBrick(AdjustObjPos(this->Character->GetLocation() + Vec2(Character->GetSize().width / 2, 0)) + Vec2(-1, 0))))
		{
			this->Character->MoveLeft();
		}
		break;
	case CBrickTable::MoveRight:
		if (IsMoveablePlace(GetBrick(AdjustObjPos(this->Character->GetLocation() - Vec2(Character->GetSize().width / 2, 0)) + Vec2(1, 0))))
		{
			this->Character->MoveRight();
		}
		break;
	case CBrickTable::Jump:
		break;
	default:
		break;
	}
}

bool CBrickTable::IsMoveablePlace(CBrick* brick)
{
	if (brick == nullptr)
	{
		return true;
	}
	else
	{
		switch (brick->Type)
		{
			case CBrick::BrickType::RedAura:
				return true;
		default:
			return false;
		}
	}
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
	auto query = this->GetBrick(this->GetCharacter()->GetPosition());
	if (query != nullptr )
	{
		switch (query->Type)
		{
		case CBrick::BrickType::RedAura:
			return 1;
			break;
		default:
			break;
		}
	}
}