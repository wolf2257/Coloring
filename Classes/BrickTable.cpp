#include "BrickTable.h"

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

void CBrickTable::AddBrick(CBrick* brick, int row, int col)
{
	brick->SetPosition(row, col);
	brick->SetLocation(GetBrickLocation(row, col));
	table.push_back(brick);
}

CBrick* CBrickTable::GetBrick(int row, int col)
{
	for (auto itr = table.begin(); itr != table.end(); ++itr) {
		if ((*itr)->GetCol() == col && (*itr)->GetRow())
		{
			return *itr;
		}
	}
	return nullptr;
}

void CBrickTable::RemoveBrick(int row, int col)
{
	table.remove(GetBrick(row, col));
}

bool CBrickTable::AddCharacter(int row, int col)
{
	this->Character = CCharacter::Create(GetBrickLocation(row, col));
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

Vec2 CBrickTable::GetBrickLocation(int row, int col)
{
	return Vec2(
		Brick00Pos.x + row * BrickSize.x, 
		Brick00Pos.y - col * BrickSize.y);
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
	//this->Character->SetLocation(this->Character->GetLocation() - Vec2(0, this->Character->GetSpeed()));
}