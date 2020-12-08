#include "Grid.h"

Grid::Grid(int map_width, int map_height, int cell_width, int cell_height)
{
	this->map_width = map_width;
	this->map_height = map_height;

	this->cell_width = cell_width;
	this->cell_height = cell_height;

	nums_col = map_width / cell_width;
	nums_row = map_height / cell_height;

	cells.resize(nums_row);

	for (int i = 0; i < nums_row; i++)
		cells[i].resize(nums_col);

	for (int i = 0; i < nums_row; i++)
		for (int j = 0; j < nums_col; j++)
			cells[i][j].clear();
}

Grid::~Grid()
{
}

void Grid::Add(LPGAMEOBJECT object)
{
	int row = (int)(object->y / cell_height);
	int col = (int)(object->x / cell_width);

	if (row > nums_row)
		return;
	if (col > nums_col)
		return;

	cells[row][col].push_back(object);
}

void Grid::Move(LPGAMEOBJECT object, float x, float y)
{
	// l?y ch? s? cell c?
	int old_row = (int)(object->y / cell_height);
	int old_col = (int)(object->x / cell_width);

	// l?y ch? s? cell m?i
	int new_row = (int)(y / cell_height);
	int new_col = (int)(x / cell_width);

	object->x = x;
	object->y = y;

	// cell không thay ??i
	if (old_row == new_row && old_col == new_col)
		return;

	for (auto it = cells[old_row][old_row].begin(); it != cells[old_row][old_row].end(); )
	{
		if ((*it) == object) {
			cells[old_row][old_row].erase(it);
		}
	}

	// thêm vào cell m?i
	Add(object);
}

void Grid::Get(D3DXVECTOR2 camPosition, vector<LPGAMEOBJECT>& listUnits)
{
	int start_col = (int)(camPosition.x / cell_width);
	int end_col = ceil((camPosition.x + SCREEN_WIDTH) / cell_width);

	if (start_col > 1)
	{
		start_col--;
	}
	if (end_col < this->nums_col)
	{
		end_col++;
	}

	for (int i = 0; i < nums_row; i++)
	{
		for (int j = start_col; j < end_col; j++)
		{
			for (auto unit : cells[i][j])
			{
				if (unit->IsEnable() == false)
					continue;
				listUnits.push_back(unit);
			}
		}
	}
}




