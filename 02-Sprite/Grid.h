#pragma once

#include <vector>
#include "GameObject.h"
typedef vector<LPGAMEOBJECT> listUnits;

class Grid
{
	int map_width;
	int map_height;

	int cell_width;
	int cell_height;

	int nums_col;
	int nums_row;

	vector<vector<listUnits>> cells;

public:
	Grid(int map_width, int map_height, int cell_width = DEFAULT_CELL_WIDTH, int cell_height = DEFAULT_CELL_HEIGHT);
	~Grid();

	void Add(LPGAMEOBJECT object);
	void Move(LPGAMEOBJECT object, float x, float y); // x, y l� to? ?? m?i c?a unit, v� v?y l�c n�y x, y c?a unit l?u v? tr� c?
	void Get(D3DXVECTOR2 camPosition, vector<LPGAMEOBJECT>& listUnits); // l?y t?t c? c�c Unit* n?m trong v�ng viewport ?? Update v� Render

};

