#include "LoadResource.h"

LoadResourceFile* LoadResourceFile::_instance = NULL;

LoadResourceFile* LoadResourceFile::GetInstance()
{
	if (_instance == NULL)
		_instance = new LoadResourceFile();
	return _instance;
}

void LoadResourceFile::LoadData(const std::string& filePath)
{
	char* fileLoc = new char[filePath.size() + 1]; // 1

		   //TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("game");

	Textures* textures = Textures::GetInstance();

	//load texture
	xml_node<>* texturesNode = rootNode->first_node("textures");
	for (xml_node<>* child = texturesNode->first_node(); child; child = child->next_sibling()) {
		int id = std::atoi(child->first_attribute("id")->value());
		int red = std::atoi(child->first_attribute("red")->value());
		int green = std::atoi(child->first_attribute("green")->value());
		int blue = std::atoi(child->first_attribute("blue")->value());
		std::string path = std::string(child->first_attribute("path")->value()); // lay path
		std::wstring cover = std::wstring(path.begin(), path.end());
		textures->Add(id, cover.c_str(), D3DCOLOR_XRGB(red, green, blue));
	}

	//load Sprite
	xml_node<>* spritesNode = rootNode->first_node("sprites");
	for (xml_node<>* child = spritesNode->first_node(); child; child = child->next_sibling()) {
		int texId = std::atoi(child->first_attribute("texid")->value());
		const char* path = child->first_attribute("path")->value(); // lay path
		LoadSpriteSheetFile(path, textures->Get(texId));
	}

	//load animation
	xml_node<>* animationsNode = rootNode->first_node("animations");
	for (xml_node<>* child = animationsNode->first_node(); child; child = child->next_sibling()) {
		const char* path = child->first_attribute("path")->value(); // lay path
		LoadAnimationsFile(path);
	}
}

void LoadResourceFile::LoadSpriteSheetFile(const char* filePath, LPDIRECT3DTEXTURE9 tex)
{
	rapidxml::file<> xmlFile(filePath);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("TextureAtlas");
	for (xml_node<>* spriteNode = rootNode->first_node(); spriteNode; spriteNode = spriteNode->next_sibling())
	{

		string idSprite;
		int left;
		int top;
		int width;
		int height;

		idSprite = spriteNode->first_attribute("n")->value();
		left = atoi(spriteNode->first_attribute("x")->value());
		top = atoi(spriteNode->first_attribute("y")->value());
		width = atoi(spriteNode->first_attribute("w")->value());
		height = atoi(spriteNode->first_attribute("h")->value());

		Sprites* sprites = Sprites::GetInstance();
		sprites->Add(idSprite, left, top, width, height, tex);
	}
}

void LoadResourceFile::LoadAnimationsFile(const char* filePath)
{
	rapidxml::file<> xmlFile(filePath);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("animations");
	int i = 0;
	for (xml_node<>* animationNode = rootNode->first_node(); animationNode; animationNode = animationNode->next_sibling())
	{

		LPANIMATION ani;

		int defaultTime = atoi(animationNode->first_attribute("defaultTime")->value());
		ani = new Animation(defaultTime);

		xml_node<>* frameNode = rootNode->first_node("frame");
		for (xml_node<>* frameNode = animationNode->first_node("frame"); frameNode; frameNode = frameNode->next_sibling())
		{
			string spriteId = string(frameNode->first_attribute("spriteID")->value());
			int time = atoi(frameNode->first_attribute("time")->value());
			ani->Add(spriteId, time);
		}

		string aniId = string(animationNode->first_attribute("ID")->value());
		Animations* animations = Animations::GetInstance();
		animations->Add(aniId, ani);
	}
}

vector<string> LoadResourceFile::GetAnimations(const char* filePath)
{
	vector<string> animationsList;

	rapidxml::file<> xmlFile(filePath);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("animations");
	int i = 0;
	for (xml_node<>* animationNode = rootNode->first_node(); animationNode; animationNode = animationNode->next_sibling())
	{

		string aniId = string(animationNode->first_attribute("ID")->value());
		animationsList.push_back(aniId);
	}

	return animationsList;
}



void LoadResourceFile::LoadTextures()
{
	//Textures* textures = Textures::GetInstance();

	//textures->Add(ID_BBOX, L"resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add(ID_TEX_SIMON, L"resources\\simon\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_GROUND, L"resources\\ground\\ground.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_WEAPON, L"resources\\weapons\\weapons.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_CANDLE, L"resources\\candle\\candle.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_ITEMS, L"resources\\items\\items.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_EFFECT, L"resources\\effect\\effect.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_SUB_WEAPONS, L"resources\\sub_weapons\\sub_weapons.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_STAIR, L"resources\\stair\\stair.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_DOOR, L"resources\\door\\door.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_GATE, L"resources\\door\\gate.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_ZOMBIE, L"resources\\zombie\\zombie.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_BLACK_LEOPARD, L"resources\\black_leopard\\black_leopard.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_VAMPIRE_BAT, L"resources\\vampire_bat\\vampire_bat.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_FISHMAN, L"resources\\fish_man\\fish_man.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_FIREBALL, L"resources\\fire_ball\\fire_ball.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_BUBBLES, L"resources\\bubbles\\bubbles.png", D3DCOLOR_XRGB(255, 0, 255));
}

void LoadResourceFile::LoadAllResource()
{
	//Textures* textures = Textures::GetInstance();

	//LoadTextures();
	//auto texGround = textures->Get(ID_TEX_GROUND);
	//auto texSimon = textures->Get(ID_TEX_SIMON);
	//auto texWeapon = textures->Get(ID_TEX_WEAPON);
	//auto texCandle = textures->Get(ID_TEX_CANDLE);
	//auto texItems = textures->Get(ID_TEX_ITEMS);
	//auto texEffect = textures->Get(ID_TEX_EFFECT);
	//auto texSubWeapons = textures->Get(ID_TEX_SUB_WEAPONS);
	//auto texStair = textures->Get(ID_TEX_STAIR);
	//auto texDoor = textures->Get(ID_TEX_DOOR);
	//auto texGate = textures->Get(ID_TEX_GATE);
	//auto texZombie = textures->Get(ID_TEX_ZOMBIE);
	//auto texBlackLeopard = textures->Get(ID_TEX_BLACK_LEOPARD);
	//auto texVampireBat = textures->Get(ID_TEX_VAMPIRE_BAT);
	//auto texFishMan = textures->Get(ID_TEX_FISHMAN);
	//auto texFireBall = textures->Get(ID_TEX_FIREBALL);
	//auto texBubbles = textures->Get(ID_TEX_BUBBLES);

	//LoadSpriteSheetFile("resources\\ground\\ground.xml", texGround);
	//LoadSpriteSheetFile("resources\\simon\\simon.xml", texSimon);
	//LoadSpriteSheetFile("resources\\weapons\\weapons.xml", texWeapon);
	//LoadSpriteSheetFile("resources\\candle\\candle.xml", texCandle);
	//LoadSpriteSheetFile("resources\\items\\items.xml", texItems);
	//LoadSpriteSheetFile("resources\\effect\\effect.xml", texEffect);
	//LoadSpriteSheetFile("resources\\sub_weapons\\sub_weapons.xml", texSubWeapons);
	//LoadSpriteSheetFile("resources\\stair\\stair.xml", texStair);
	//LoadSpriteSheetFile("resources\\door\\door.xml", texDoor);
	//LoadSpriteSheetFile("resources\\door\\gate.xml", texGate);
	//LoadSpriteSheetFile("resources\\zombie\\zombie.xml", texZombie);
	//LoadSpriteSheetFile("resources\\black_leopard\\black_leopard.xml", texBlackLeopard);
	//LoadSpriteSheetFile("resources\\vampire_bat\\vampire_bat.xml", texVampireBat);
	//LoadSpriteSheetFile("resources\\fish_man\\fish_man.xml", texFishMan);
	//LoadSpriteSheetFile("resources\\fire_ball\\fire_ball.xml", texFireBall);
	//LoadSpriteSheetFile("resources\\bubbles\\bubbles.xml", texBubbles);

	//LoadAnimationsFile("resources\\simon\\simon_ani.xml");
	//LoadAnimationsFile("resources\\weapons\\weapons_ani.xml");
	//LoadAnimationsFile("resources\\ground\\ground_ani.xml");
	//LoadAnimationsFile("resources\\candle\\candle_ani.xml");
	//LoadAnimationsFile("resources\\items\\items_ani.xml");
	//LoadAnimationsFile("resources\\effect\\effect_ani.xml");
	//LoadAnimationsFile("resources\\sub_weapons\\sub_weapons_ani.xml");
	//LoadAnimationsFile("resources\\stair\\stair_ani.xml");
	//LoadAnimationsFile("resources\\door\\door_ani.xml");
	//LoadAnimationsFile("resources\\door\\gate_ani.xml");
	//LoadAnimationsFile("resources\\zombie\\zombie_ani.xml");
	//LoadAnimationsFile("resources\\black_leopard\\black_leopard_ani.xml");
	//LoadAnimationsFile("resources\\vampire_bat\\vampire_bat_ani.xml");
	//LoadAnimationsFile("resources\\fish_man\\fish_man_ani.xml");
	//LoadAnimationsFile("resources\\fire_ball\\fire_ball_ani.xml");
	//LoadAnimationsFile("resources\\bubbles\\bubbles_ani.xml");
}
