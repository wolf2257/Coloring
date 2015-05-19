#include "BrickTable.h"

using namespace std;
USING_NS_CC;

Vec2 CBrickTable::BrickSize = Vec2(55, 56);

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
	Table->table = new CBrick**[cols];
	for (int i = 0; i < cols; ++i) {
		Table->table[i] = new CBrick*[rows];
		memset(Table->table[i], 0, sizeof(int)*rows);
	}

	Table->Brick00Pos = Vec2(Axis.x - rows * BrickSize.x / 2 + BrickSize.x / 2, Axis.y + cols * BrickSize.y / 2 - BrickSize.y / 2);

	return Table;
}

bool CBrickTable::AddBrick(CBrick* brick, int row, int col)
{
	if (table[col][row] == nullptr)
	{
		table[col][row] = brick;
		brick->SetLocation(GetBrickLocation(row, col));
		return true;
	}
	return false;
}

CBrick* CBrickTable::GetBrick(int row, int col)
{
	if (table[col][row] != nullptr)
	{
		return table[col][row];
	}
	return nullptr;
}

bool CBrickTable::RemoveBrick(int row, int col)
{
	return AddBrick(nullptr, row, col);
}

Vec2 CBrickTable::GetBrickLocation(int row, int col)
{
	return Vec2(
		Brick00Pos.x + row * BrickSize.x, 
		Brick00Pos.y - col * BrickSize.y);
}


void CBrickTable::AttatchAll(Layer* layer, int zOrder)
{
	for (size_t i = 0; i < cols; i++)
	{
		for (size_t j = 0; j < rows; j++)
		{
			if (table[i][j] != nullptr)
			{
				table[i][j]->Attatch(layer, zOrder);
			}
		}
	}
}