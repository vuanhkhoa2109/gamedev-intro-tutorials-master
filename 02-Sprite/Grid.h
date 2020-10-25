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
	void Move(LPGAMEOBJECT object, float x, float y); // x, y là to? ?? m?i c?a unit, vì v?y lúc này x, y c?a unit l?u v? trí c?
	void Get(D3DXVECTOR2 camPosition, vector<LPGAMEOBJECT>& listUnits); // l?y t?t c? các Unit* n?m trong vùng viewport ?? Update và Render

};

