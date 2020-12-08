#pragma once

#include <map>

#include "Game.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Grid.h"
#include "Simon.h"

#include "Candle.h"
#include "Ground.h"
#include "Weapon.h"
#include "Items.h"
#include "GetHiddenMoneyObject.h"
#include "debug.h"
#include "BlackLeopard.h"
#include "Zombie.h"
#include "FishMan.h"
#include "FireBall.h"
#include "Water.h"
#include "VampireBat.h"
#include "MoneyBagFlashing.h"
#include "Stair.h"
#include "GUI.h"
#include "Boss.h"
#include "SubWeapon.h"
#include "Door.h"
#include "ChangeSceneBlock.h"
#include "BreakWall.h"

using namespace std;

class SceneManager
{
	int IDScene;

	Game* game;
	Grid* grid;

	vector<LPGAMEOBJECT> listUnits;
	vector<LPGAMEOBJECT> listObjects;
	vector<LPGAMEOBJECT> listItems;
	vector<LPGAMEOBJECT> listStairs;

	Simon* simon;
	Items* item;
	Weapon* weapon;
	SubWeapon* subweapon;
	Stair* stair;
	FireBall* fireball;
	Bubble* bubble;
	Boss* boss;
	GUI* gui;
	Water* water;
	FishMan* fishman;

	TileMaps* tilemaps = TileMaps::GetInstance();
	Textures* textures = Textures::GetInstance();
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	vector<SubWeapon*> subweaponList;
	vector<LPGAMEOBJECT> listStaticObjectsToRender;
	vector<LPGAMEOBJECT> listMovingObjectsToRender;
	vector<LPGAMEOBJECT> listDoors;

	bool stopWatchMoment = false;

	bool isSetSimonAutoWalk = false;
	bool isMovingCamera1 = false;
	bool isMovingCamera2 = false;
	int countDxCamera = 0;

	bool isBossFighting = false;
	bool isSimonDead = false;

	DWORD timeGamer = 300;
	DWORD timeGamerCount = 0;

public:
	Timer* stopWatchTimer = new Timer(WEAPONS_STOP_WATCH_TIME);
	Timer* simonDeadTimer = new Timer(SIMON_DEAD_TIME);
	Timer* crossEffectTimer = new Timer(ITEM_CROSS_EFFECT_TIME);
	Timer* doubleShotTimer = new Timer(ITEM_DOUBLE_SHOT_EFFECT_TIME);
	Timer* tripleShotTimer = new Timer(ITEM_TRIPLE_SHOT_EFFECT_TIME);

	SceneManager(Game* game);
	~SceneManager();

	bool isGameReset = false;

	void Init(int idScene);						// init simon position, camera position, grid..
	void LoadResources();						// load all sprites, textures and tilemaps
	void LoadObjectsFromFile(LPCWSTR FilePath);	// load all objects (position, state, isEnable) from file 

	void GetObjectFromGrid();

	void Update(DWORD dt);
	void UpdateTimeCounter();
	void UpdateCameraPosition();
	void UpdateGrid();
	void UpdateTimeGamer();

	void Render();

	bool SimonWalkThroughDoor();			

	string GetRandomItem();						
	void SetDropItems();				

	bool IsInViewport(LPGAMEOBJECT object);
	void SetInactivationByPosition();			

	void ChangeScene();					

	void SetGameState(int state);				
	void ResetGame();						

	// Get, Set
	int GetIDScene() { return this->IDScene; }
	Simon* GetSimon() { return this->simon; }
	Boss* GetBoss() { return this->boss; }
	vector<SubWeapon*>* GetWeaponList() { return &subweaponList; }
	vector<LPGAMEOBJECT>* GetListStairs() { return &(listStairs); }
	GUI* GetUI() { return this->gui; }

	bool IsMovingCamera() { return isMovingCamera1 || isMovingCamera2; }

	// Item Effect
	void CrossEffect();
	void DoubleShotEffect();
	void TripleShotEffect();

	// Các hàm con c?a hàm Update()
	void Simon_Update(DWORD dt);
	void Weapon_Update(DWORD dt, int index);
	void Item_Update(DWORD dt, LPGAMEOBJECT& object);
	void Zombie_Update(DWORD dt, LPGAMEOBJECT& object);
	void BlackLeopard_Update(DWORD dt, LPGAMEOBJECT& object);
	void VampireBat_Update(DWORD dt, LPGAMEOBJECT& object);
	void FishMan_Update(DWORD dt, LPGAMEOBJECT& object);
	void Boss_Update(DWORD dt, LPGAMEOBJECT& object);
};

