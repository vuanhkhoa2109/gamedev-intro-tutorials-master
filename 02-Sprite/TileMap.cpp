#include "TileMap.h"

TileMap::TileMap(int ID, LPCWSTR filePathTex, LPCWSTR filePathData, int mapWidth, int mapHeight, int tileWidth, int tileHeight)
{
	this->ID = ID;
	this->filePathTex = filePathTex;
	this->filePathData = filePathData;

	sprites = Sprites::GetInstance();

	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	numsRow = mapHeight / tileHeight;
	numsCol = mapWidth / tileWidth;

	LoadResources();
	LoadMapData();
	CreateZoneToDraw();
}

void TileMap::LoadResources()
{
	Textures* texture = Textures::GetInstance();

	texture->Add(ID, filePathTex, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texTileMap = texture->Get(ID);

	// l?y thông tin v? kích th??c c?a texture 
	D3DSURFACE_DESC surfaceDesc;
	int level = 0;
	texTileMap->GetLevelDesc(level, &surfaceDesc);

	// tính toán s? hàng, s? c?t c?n thi?t ?? load tile 
	int numsRowToRead = surfaceDesc.Height / tileHeight;
	int numsColToRead = surfaceDesc.Width / tileWidth;

	// th?c hi?n l?u danh sách các tile vô sprites theo th? t? id_sprite
	int id_sprite = 1;

	for (int i = 0; i < numsRowToRead; i++)
	{
		for (int j = 0; j < numsColToRead; j++)
		{
			int left = tileWidth * j;
			int top = tileHeight * i;
			int width = tileWidth;
			int height = tileHeight;
			sprites->Add(to_string(id_sprite + ID * 1000), left, top, width, height, texTileMap);
			id_sprite += 1;
		}
	}
}

void TileMap::LoadMapData()
{
	fstream fs;
	fs.open(filePathData, ios::in);

	if (fs.fail())
	{
		DebugOut(L"[ERROR] TileMap::LoadMapData failed: ID=%d", ID);
		fs.close();
		return;
	}

	string line;

	while (!fs.eof())
	{
		getline(fs, line);

		// tách s? t? chu?i ??c ???c
		vector<int> numInLine;
		stringstream ss(line);
		int n;

		while (ss >> n) {
			numInLine.push_back(n);
		}

		// thêm vào ma tr?n mapData
		mapData.push_back(numInLine);
	}


	fs.close();
}

void TileMap::CreateZoneToDraw()
{

	rapidxml::file<> xmlFile("Scenes\\game.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("scenes");

	for (xml_node<>* sceneNode = rootNode->first_node(); sceneNode; sceneNode = sceneNode->next_sibling()) {
		int sceneID = std::atoi(sceneNode->first_attribute("sceneID")->value());
		if (ID == sceneID)
		{
			for (xml_node<>* mapLimitNode = sceneNode->first_node("mapLimit"); mapLimitNode; mapLimitNode = mapLimitNode->next_sibling())
			{
				int min_col = std::atoi(mapLimitNode->first_attribute("min_col")->value());
				int max_col = std::atoi(mapLimitNode->first_attribute("max_col")->value());
				min_max_col_to_draw.push_back({ min_col, max_col });
			}
		}
	}

	//switch (ID)
	//{
	//case SCENE_1:
	//	min_max_col_to_draw.push_back({ 0, 48 });
	//	break;
	//case SCENE_2:
	//	min_max_col_to_draw.push_back({ 0, 96 });
	//	min_max_col_to_draw.push_back({ 96, 128 });
	//	min_max_col_to_draw.push_back({ 128, 176 });
	//	break;
	//case SCENE_3:
	//	min_max_col_to_draw.push_back({ 0, 32 });
	//	break;
	//default:
	//	break;
	//}
}

void TileMap::Draw(D3DXVECTOR2 camPosition, bool isCrossEffect)
{
	start_col_to_draw = (int)camPosition.x / 32;
	end_col_to_draw = start_col_to_draw + SCREEN_WIDTH / 32;

	int alpha = 255;
	if (isCrossEffect == true) alpha = rand() % 255;

	for (int i = 0; i < numsRow; i++)
	{
		for (int j = start_col_to_draw; j <= end_col_to_draw; j++)
		{
			// +camPosition.x ?? luôn gi? camera ? chính gi?a, vì trong hàm draw có tr? cho camPosition.x làm các object ??u di chuy?n theo
			// +(int)camPosition.x % 32 ?? gi? cho camera chuy?n ??ng m??t (th?c ra giá tr? này b?ng vx*dt, chính là quãng ???ng d?ch chuy?n c?a simon)
			float x = tileWidth * (j - start_col_to_draw) + camPosition.x - (int)camPosition.x % 32;
			float y = tileHeight * i + 80;

			string tile = to_string(mapData[i][j] + ID * 1000);
			sprites->Get(tile)->Draw(-1, x, y, alpha);
		}
	}
}

TileMaps* TileMaps::_instance = NULL;

void TileMaps::Add(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width, int tile_height)
{
	LPTILEMAP tilemap = new TileMap(ID, filePath_tex, filePath_data, map_width, map_height, tile_width, tile_height);
	tilemaps[ID] = tilemap;
}

TileMaps* TileMaps::GetInstance()
{
	if (_instance == NULL) _instance = new TileMaps();
	return _instance;
}

