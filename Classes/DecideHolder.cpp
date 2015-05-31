#include "DecideHolder.h"

using namespace std;
USING_NS_CC;

Vec2 CDecideHolder::BrickSize = Vec2(220, 230);

CDecideHolder::CDecideHolder()
{
}


CDecideHolder::~CDecideHolder()
{
}


CDecideHolder* CDecideHolder::Create(int rows, int cols, Vec2 Axis)
{
	auto Table = new CDecideHolder();

	Table->rows = rows;
	Table->cols = cols;

	// Array allocation
	Table->table = new CLevelButton**[cols];
	for (int i = 0; i < cols; ++i) {
		Table->table[i] = new CLevelButton*[rows];
		memset(Table->table[i], 0, sizeof(int)*rows);
	}

	Table->Brick00Pos = Vec2(Axis.x - rows * BrickSize.x / 2 + BrickSize.x / 2, Axis.y + cols * BrickSize.y / 2 - BrickSize.y / 2);

	return Table;
}

bool CDecideHolder::AddBrick(CLevelButton* brick, int row, int col)
{
	if (table[col][row] == nullptr)
	{
		table[col][row] = brick;
		brick->SetLocation(GetBrickLocation(row, col));
		return true;
	}
	return false;
}

CLevelButton* CDecideHolder::GetBrick(int row, int col)
{
	if (table[col][row] != nullptr)
	{
		return table[col][row];
	}
	return nullptr;
}

bool CDecideHolder::RemoveBrick(int row, int col)
{
	return AddBrick(nullptr, row, col);
}

Vec2 CDecideHolder::GetBrickLocation(int row, int col)
{
	return Vec2(
		Brick00Pos.x + row * BrickSize.x,
		Brick00Pos.y - col * BrickSize.y);
}


void CDecideHolder::AttatchAll(Layer* layer, int zOrder)
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