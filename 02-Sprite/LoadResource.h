#pragma once
#include <d3dx9.h>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include "Const.h"

using namespace std;

using namespace rapidxml;

class LoadResourceFile
{
	static LoadResourceFile* _instance;
public:
	static LoadResourceFile* GetInstance();

	void LoadSpriteSheetFile(const char* filePath, LPDIRECT3DTEXTURE9 tex);
	void LoadAnimationsFile(const char* filePath);
	void LoadTextures();
	vector<string> GetAnimations(const char* filePath);
	void LoadData(const std::string& filePath);

	void LoadAllResource();
};

