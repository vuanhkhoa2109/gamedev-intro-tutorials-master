#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Textures.h"
#include "Debug.h"
#include "Sprites.h"
#include "Const.h"
#include "LoadResource.h"

using namespace std;

class TileMap
{
	int mapWidth;			// chi?u r?ng c?a map
	int mapHeight;			// chi?u cao c?a map

	int numsRow;			// s? hàng c?a map
	int numsCol;			// s? c?t c?a map

	int tileWidth;			// chi?u r?ng m?t tile
	int tileHeight;		// chi?u cao m?t tile

	LPCWSTR filePathTex;
	LPCWSTR filePathData;
	int ID;					// ID c?a tile map, dùng ?? t?o class qu?n lí TileMaps sau này ...

public:
	vector<vector<int>> mapData;	// ma tr?n l?u d? li?u map

	vector<vector<int>> min_max_col_to_draw;
	int index = 0; // index hi?n t?i c?a min_max_col_to_draw

	int start_col_to_draw;
	int end_col_to_draw;

	Sprites* sprites;

	TileMap(int ID, LPCWSTR filePathTex, LPCWSTR filePathData, int mapWidth, int mapHeight, int tileWidth, int tileHeight);

	void LoadResources();	// load t?t c? các block tile l?u vào sprites
	void LoadMapData();	// load ma tr?n d? li?u map 
	void CreateZoneToDraw(); // kh?i t?o vector 2 chi?u min_max_col_to_draw
	void Draw(D3DXVECTOR2 camPosition, bool isCrossEffect = false);	// v? t?t c? các tile n?m trong camera

	int GetMapWidth() { return mapWidth; }
};

typedef TileMap* LPTILEMAP;

class TileMaps
{
	static TileMaps* _instance;
	unordered_map<int, LPTILEMAP> tilemaps;

public:
	void Add(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width = 32, int tile_height = 32);
	LPTILEMAP Get(int ID) { return tilemaps[ID]; }

	static TileMaps* GetInstance();
};

