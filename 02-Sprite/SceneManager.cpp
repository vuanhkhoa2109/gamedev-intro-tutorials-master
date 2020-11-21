#include "SceneManager.h"
#include "debug.h"


SceneManager::SceneManager(Game* game)
{
	this->game = game;
	LoadResources();

	// INIT
	simon = new Simon();
}

SceneManager::~SceneManager()
{

}

void SceneManager::Init(int idScene)
{
	IDScene = idScene;

	switch (idScene)
	{
	case SCENE_1:
		grid = new Grid(1536, 480);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1);
		SetGameState(GAMESTATE_1);
		break;
	case SCENE_2:
		grid = new Grid(5632, 480);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_2);
		SetGameState(GAMESTATE_2_1);
		break;
	case SCENE_3:
		grid = new Grid(1024, 480);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_3);
		simon->SetState(STAIR_DOWN);
		SetGameState(GAMESTATE_3_1);
		break;
	default:
		break;
	}
}

void SceneManager::LoadResources()
{

	LoadResourceFile* LoadResourceFile = LoadResourceFile::GetInstance();
	LoadResourceFile->LoadData("resources\\data.xml");


	simon = new Simon();

	candle = new Candle();

	/*candle = new Candle();

	item = new Items();

	weapon = new Weapon();

	subweapon = new SubWeapon();

	door = new Door();

	zombie = new Zombie();

	leopard = new BlackLeopard();

	fishman = new FishMan();

	fireball = new FireBall();

	bubble = new Bubble();

	bat = new VampireBat();

	boss = new Boss();*/

	tilemaps->Add(SCENE_1, FILEPATH_TEX_MAP_SCENE_1, FILEPATH_DATA_MAP_SCENE_1, 1536, 320);
	tilemaps->Add(SCENE_2, FILEPATH_TEX_MAP_SCENE_2, FILEPATH_DATA_MAP_SCENE_2, 5632, 352);
	tilemaps->Add(SCENE_3, FILEPATH_TEX_MAP_SCENE_3, FILEPATH_DATA_MAP_SCENE_3, 1024, 352);
}

void SceneManager::LoadObjectsFromFile(LPCWSTR FilePath)
{
	fstream fs;
	fs.open(FilePath, ios::in);
	if (fs.fail())
	{
		DebugOut(L"[INFO] Scene %d load data failed: file path = %s\n", IDScene, FilePath);
		fs.close();
		return;
	}

	string ID_Obj;
	float pos_x, pos_y;
	string state;
	bool isEnable;
	string nameItem;
	string typeStair;

	while (!fs.eof())
	{
		fs >> ID_Obj >> pos_x >> pos_y >> state >> isEnable >> nameItem >> typeStair;
		if (ID_Obj == CANDLE)
		{
			candle = new Candle();
			candle->SetPosition(pos_x, pos_y);
			candle->SetState(state);
			candle->isEnable = isEnable;
			candle->SetIdItem(nameItem);
			grid->Add(candle);
		}
		else if (ID_Obj == GROUND)
		{
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->isEnable = isEnable;
			grid->Add(ground);
		}
		if (ID_Obj == GROUND)
		{
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->isEnable = isEnable;
			grid->Add(ground);
		}
		/*if (ID_Obj == CANDLE)
		{
			candle = new Candle();
			candle->SetPosition(pos_x, pos_y);
			candle->SetState(state);
			candle->isEnable = isEnable;
			candle->SetIdItem(nameItem);
			grid->Add(candle);
		}
		else if (ID_Obj == GROUND)
		{
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->isEnable = isEnable;
			grid->Add(ground);
		}
		else if (ID_Obj == STAIR)
		{
			stair = new Stair();
			stair->SetPosition(pos_x, pos_y);
			stair->SetState(state);
			stair->SetEnable(isEnable);
			stair->SetType(typeStair);
			listStairs.push_back(stair);
			grid->Add(stair);
		}
		else if (ID_Obj == DOOR)
		{
			door = new Door();
			door->SetPosition(pos_x, pos_y);
			door->SetState(state);
			door->SetEnable(isEnable);
			grid->Add(door);
		}
		else if (ID_Obj == ZOMBIE)
		{
			zombie = new Zombie();
			zombie->SetPosition(pos_x, pos_y);
			zombie->SetEntryPosition(pos_x, pos_y);
			zombie->SetState(state);
			zombie->SetEnable(isEnable);
			grid->Add(zombie);
		}
		else if (ID_Obj == BLACK_LEOPARD)
		{
			leopard = new BlackLeopard();
			leopard->SetPosition(pos_x, pos_y);
			leopard->SetEntryPosition(pos_x, pos_y);
			leopard->SetState(INACTIVE);
			leopard->SetEnable(true);
			grid->Add(leopard);
		}
		else if (ID_Obj == VAMPIRE_BAT)
		{
			bat = new VampireBat();
			bat->SetPosition(pos_x, pos_y);
			bat->SetEntryPosition(pos_x, pos_y);
			bat->SetState(VAMPIRE_BAT_INACTIVE);
			bat->SetEnable(true);
			grid->Add(bat);
		}
		else if (ID_Obj == FISHMAN)
		{
			fishman = new FishMan();
			fishman->SetPosition(pos_x, pos_y);
			fishman->SetEntryPosition(pos_x, pos_y);
			fishman->SetState(FISHMAN_INACTIVE);
			fishman->SetEnable(true);
			grid->Add(fishman);
		}
		else if (ID_Obj == BOSS)
		{
			boss = new Boss();
			boss->SetPosition(pos_x, pos_y);
			boss->SetEntryPosition(pos_x, pos_y);
			boss->SetPosition(pos_x, pos_y);
			boss->SetState(BOSS_INACTIVE);
			boss->SetIdItem(nameItem);
			boss->SetEnable(true);
			grid->Add(boss);
		}
		else if (ID_Obj == CHANGE_SCENE_OBJECT)
		{
			ChangeSceneObject* changeScene = new ChangeSceneObject();
			changeScene->SetPosition(pos_x, pos_y);
			changeScene->SetIDNextScene(atoi(state.c_str()));
			changeScene->SetEnable(true);
			grid->Add(changeScene);
		}
		else if (ID_Obj == WATER)
		{
			water = new Water();
			water->SetPosition(pos_x, pos_y);
			water->SetEnable(true);
			grid->Add(water);
		}
		else if (ID_Obj == BREAKWALL)
		{
			BreakWall* breakwall = new BreakWall();
			breakwall->SetPosition(pos_x, pos_y);
			breakwall->SetEnable(true);
			breakwall->SetState(NORMAL);
			breakwall->SetIdItem(nameItem);
			grid->Add(breakwall);
		}*/
	}
	fs.close();
}

void SceneManager::GetObjectFromGrid()
{
	listObjects.clear();
	listStairs.clear();
	listDoors.clear();
	listStaticObjectsToRender.clear();
	listMovingObjectsToRender.clear();
	listUnits.clear();

	grid->Get(game->GetCamPos(), listUnits);

	//DebugOut(L"%d \n", listUnits.size());

	for (UINT i = 0; i < listUnits.size(); i++)
	{
		LPGAMEOBJECT obj = listUnits[i];
		listObjects.push_back(obj);
		if (dynamic_cast<Ground*>(obj))
			continue;
		if (dynamic_cast<Ground*>(obj))
			continue;
		/*if (dynamic_cast<Ground*>(obj))
			continue;
		else if (dynamic_cast<Stair*>(obj))
			listStairs.push_back(obj);
		else if (dynamic_cast<Door*>(obj))
			listDoors.push_back(obj);
		else if (dynamic_cast<Candle*>(obj) ||
			dynamic_cast<Water*>(obj) || dynamic_cast<BreakWall*>(obj))
			listStaticObjectsToRender.push_back(obj);
		else*/
			listMovingObjectsToRender.push_back(obj);
	}
}

void SceneManager::Update(DWORD dt)
{
	// N?u Simon ?i qua c?a thì không c?n c?p nh?t hay xét va ch?m
	if (SimonWalkThroughDoor() == true)
		return;

	// Khi Simon va ch?m v?i ChangScene objects, ti?n hành thay ??i, c?p nh?t tr?ng thái
	if (simon->changeScene != -1)
	{
		ChangeScene();
		simon->changeScene = -1;
	}

	// L?y danh sách object t? grid 
	GetObjectFromGrid();

	// Cross effect
	CrossEffect();

	// C?p nh?t b? ??m th?i gian
	UpdateTimeCounter();

	// double shot
	DoubleShotEffect();

	// triple shot
	TripleShotEffect();

	// Drop item
	SetDropItems();

	// Update
	Simon_Update(dt);

	for (int i = 0; i < 3; i++)
		Weapon_Update(dt, i);

	for (UINT i = 0; i < listObjects.size(); i++)
	{
		LPGAMEOBJECT object = listObjects[i];

		/*if (dynamic_cast<Items*>(object))
			Item_Update(dt, object);
		else if (dynamic_cast<Zombie*>(object))
			Zombie_Update(dt, object);
		else if (dynamic_cast<BlackLeopard*>(object))
			BlackLeopard_Update(dt, object);
		else if (dynamic_cast<VampireBat*>(object))
			VampireBat_Update(dt, object);
		else if (dynamic_cast<FishMan*>(object))
			FishMan_Update(dt, object);
		else if (dynamic_cast<Boss*>(object))
			Boss_Update(dt, object);
		else*/
			object->Update(dt, &listObjects);
	}

	// Không cho Simon ?i ra kh?i vùng ?ánh boss
	if (isBossFighting == true && simon->x < game->GetCamPos().x)
		simon->x = game->GetCamPos().x;

	// Xoá các object ?i ra kh?i vùng viewport
	SetInactivationByPosition();

	// update camera
	UpdateCameraPosition();

	// update grid
	UpdateGrid();
}

void SceneManager::UpdateTimeCounter()
{
	// Stop Watch
	//if (stopWatchTimer->IsTimeUp() == true)
	//{
	//	stopWatchTimer->Stop();
	//	stopWatchMoment = false;
	//}
	//else
	//{
	//	stopWatchMoment = true;
	//}

	//// Cross
	//if (crossEffectTimer->IsTimeUp() == true)
	//	crossEffectTimer->Stop();

	//// Simon dead
	//if (isSimonDead == true && simonDeadTimer->IsTimeUp() == true)
	//{
	//	simonDeadTimer->Stop();
	//	isSimonDead = false;
	//	ResetGame();
	//}

	//// Double shot
	//if (doubleShotTimer->IsTimeUp() == true)
	//	doubleShotTimer->Stop();

	//// Triple shot
	//if (tripleShotTimer->IsTimeUp() == true)
	//	tripleShotTimer->Stop();
}

void SceneManager::Render()
{
	tilemaps->Get(IDScene)->Draw(game->GetCamPos(), !crossEffectTimer->IsTimeUp());

	for (auto obj : listStaticObjectsToRender)
	{
		obj->Render();
		//obj->RenderBoundingBox();
	}

	for (auto obj : listMovingObjectsToRender)
	{
		obj->Render();
		//obj->RenderBoundingBox();
		//obj->RenderActiveBoundingBox();
	}

	simon->Render();
	//simon->RenderBoundingBox();

	//for (int i = 0; i < 3; i++)
	//{
	//	subweaponList[i]->Render();
	//}

	//for (auto obj : listDoors)
	//{
	//	obj->Render();
	//	//obj->RenderBoundingBox();
	//}
}

void SceneManager::UpdateCameraPosition()
{
	if (isBossFighting == true)				// Boss fight -> not moving camera
		return;

	/*if (boss->GetState() == BOSS_ACTIVE)
	{
		isBossFighting = true;
		return;
	}*/

	if (simon->x > SCREEN_WIDTH / 2 &&
		simon->x + SCREEN_WIDTH / 2 < tilemaps->Get(IDScene)->GetMapWidth())
	{
		TileMap* map = tilemaps->Get(IDScene);
		int min_col = map->min_max_col_to_draw[map->index][0];
		int max_col = map->min_max_col_to_draw[map->index][1];

		if (simon->x >= min_col * 32 + (SCREEN_WIDTH / 2 - 16) &&
			simon->x <= max_col * 32 - (SCREEN_WIDTH / 2 - 16))
		{
			game->SetCamPos(simon->x - SCREEN_WIDTH / 2, 0);
		}
	}
}

void SceneManager::UpdateGrid()
{
	for (int i = 0; i < listUnits.size(); i++)
	{
		LPGAMEOBJECT obj = listUnits[i];

		if (obj->IsEnable() == false)
			continue;

		float newPos_x, newPos_y;
		obj->GetPosition(newPos_x, newPos_y);
		grid->Move(listUnits[i], newPos_x, newPos_y);
	}
}

bool SceneManager::SimonWalkThroughDoor()
{
	// C?p nh?t tr?ng thái Simon ?i qua c?a:
	// Di chuy?n Camera -> M? c?a -> AutoWalk -> Di chuy?n Camera

	if (simon->isWalkThroughDoor == true && simon->isTouchGround == true)
	{
		simon->isWalkThroughDoor = false;
		//simon->isFalling = false;
		simon->SetN(DIR_RIGHT);
		simon->SetState(IDLE);

		isMovingCamera1 = true;
		countDxCamera = 0;
	}

	if (isMovingCamera1 == true)
	{
		if (countDxCamera < 240)			// Di chuy?n camera m?t ?o?n 224
		{
			countDxCamera += 2;

			D3DXVECTOR3 cam = game->GetCamPos();
			game->SetCamPos(cam.x + 2, cam.y);

			return true;
		}

		if (isSetSimonAutoWalk == false)	// AutoWalk
		{
			isSetSimonAutoWalk = true;

			simon->SetState(WALK);
			simon->vy = 0;
			simon->AutoWalk(120, IDLE, DIR_RIGHT);
		}
		else
		{
			if (simon->isAutoWalk == false)
			{
				isMovingCamera2 = true;

				if (countDxCamera < 480)	// Di chuy?n camera thêm m?t ?o?n -> 480
				{
					countDxCamera += 2;

					D3DXVECTOR3 cam = game->GetCamPos();
					game->SetCamPos(cam.x + 2, cam.y);

					return true;
				}
				else
				{
					isMovingCamera1 = false;
					isMovingCamera2 = false;
					isSetSimonAutoWalk = false;
					countDxCamera = 0;

					tilemaps->Get(IDScene)->index += 1;  // t?ng gi?i h?n min_max_col c?a tilemap
				}
			}
		}
	}

	return false;
}

string SceneManager::GetRandomItem()
{
	vector<string> listItems = {
		STOP_WATCH,
		DAGGER,
		AXE,
		BOOMERANG,
		SMALL_HEART,
		LARGE_HEART,
		INVISIBILITY_POTION,
		CHAIN,
		MONEY_BAG_RED,
		MONEY_BAG_BLUE,
		MONEY_BAG_WHITE,
		MONEY_BAG_FLASHING,
		DOUBLE_SHOT,
		TRIPLE_SHOT,
		PORK_CHOP };

	bool canDropItem = (rand() % 100) < 50 ? true : false; // t? l? r?t item là 80/100

	if (canDropItem == false)
		return "";

	int randomItem = rand() % 15;

	return listItems[randomItem];
}

void SceneManager::SetDropItems()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		LPGAMEOBJECT object = listObjects[i];
		string idItem = "";
		float x, y;

		if (object->IsDroppedItem() == true)
			continue;

		/*if (dynamic_cast<Candle*>(object) && object->GetState() == CANDLE_DESTROYED)
		{
			idItem = object->nameItem;
			object->GetPosition(x, y);
			object->SetIsDroppedItem(true);
		}
		else if (dynamic_cast<BreakWall*>(object)
			&& object->GetState() == BREAK && object->IsDroppedItem() == false)
		{
			idItem = object->nameItem;
			object->GetPosition(x, y);
			object->SetIsDroppedItem(true);
		}
		else if (dynamic_cast<Boss*>(object) && object->GetState() == BOSS_DESTROYED)
		{
			if (boss->DropItem() == true)
			{
				boss->SetEnable(false);
				idItem = MAGIC_CRYSTAL;
				boss->SetIsDroppedItem(true);
				x = game->GetCamPos().x + SCREEN_WIDTH / 2;
				y = game->GetCamPos().y + SCREEN_HEIGHT / 2;
			}
		}
		else if ((dynamic_cast<Zombie*>(object) && object->GetState() == ZOMBIE_DESTROYED) ||
			(dynamic_cast<VampireBat*>(object) && object->GetState() == VAMPIRE_BAT_DESTROYED) ||
			(dynamic_cast<FishMan*>(object) && object->GetState() == FISHMAN_DESTROYED))
		{
			idItem = GetRandomItem();
			object->GetPosition(x, y);
			object->SetIsDroppedItem(true);
		}*/

		//if (idItem != "")
		//{
		//	// T?o m?t item theo id

		//	auto item = new Items();
		//	item->SetEnable(true);
		//	item->SetPosition(x, y);
		//	item->SetState(idItem);
		//	grid->Add(item);
		//	listItems.push_back(item);
		//}
	}
}

bool SceneManager::IsInViewport(LPGAMEOBJECT object)
{
	D3DXVECTOR2 camPosition = game->GetCamPos();

	float obj_x, obj_y;
	object->GetPosition(obj_x, obj_y);

	return obj_x >= camPosition.x && obj_x < camPosition.x + SCREEN_WIDTH
		&& obj_y >= camPosition.y && obj_y < camPosition.y + SCREEN_HEIGHT;
}

void SceneManager::SetInactivationByPosition()
{
	for (auto object : listObjects)
	{
		if (IsInViewport(object) == false)
		{
			/*if (dynamic_cast<Zombie*>(object) && object->GetState() == ZOMBIE_ACTIVE)
			{
				auto zombie = dynamic_cast<Zombie*>(object);
				zombie->SetState(ZOMBIE_INACTIVE);
			}
			else if (dynamic_cast<BlackLeopard*>(object) && object->GetState() == BLACK_LEOPARD_ACTIVE)
			{
				auto leopard = dynamic_cast<BlackLeopard*>(object);
				leopard->SetState(BLACK_LEOPARD_INACTIVE);
			}
			else if (dynamic_cast<VampireBat*>(object) && object->GetState() == VAMPIRE_BAT_ACTIVE)
			{
				auto bat = dynamic_cast<VampireBat*>(object);
				bat->SetState(VAMPIRE_BAT_INACTIVE);
			}
			else if (dynamic_cast<FishMan*>(object)
				&& (object->GetState() == FISHMAN_ACTIVE || object->GetState() == FISHMAN_JUMP))
			{
				auto fishman = dynamic_cast<FishMan*>(object);
				fishman->SetState(FISHMAN_INACTIVE);
			}
			else if (dynamic_cast<FireBall*>(object) && object->IsEnable() == true)
				object->SetEnable(false);
			else if (dynamic_cast<Items*>(object) && object->IsEnable() == true)
				object->SetEnable(false);*/
		}
	}

	for (int i = 0; i < 3; i++)
	{
		/*if (subweaponList[i]->IsEnable() == true)
		{
			if (IsInViewport(subweaponList[i]) == false)
				subweaponList[i]->SetEnable(false);
		}*/
	}
}

void SceneManager::ChangeScene()
{
	float x, y;
	simon->GetPosition(x, y);

	if (IDScene == SCENE_2 && simon->changeScene == SCENE_3)
	{
		Init(SCENE_3);

		if (x < 3200) SetGameState(GAMESTATE_3_1);
		else SetGameState(GAMESTATE_3_2);
	}
	else if (IDScene == SCENE_3 && simon->changeScene == SCENE_2)
	{
		Init(SCENE_2);

		if (x < 320) SetGameState(GAMESTATE_2_2_1);
		else SetGameState(GAMESTATE_2_2_2);
	}
	else if (IDScene == SCENE_1 && simon->changeScene == SCENE_2)
		Init(SCENE_2);
}

void SceneManager::SetGameState(int state)
{
	switch (state)
	{
	case GAMESTATE_1:
		simon->SetState(IDLE);
		simon->SetPosition(0, 302);
		game->SetCamPos(0, 0);
		tilemaps->Get(SCENE_1)->index = 0;
		break;
	case GAMESTATE_2_1:
		simon->SetState(IDLE);
		simon->SetPosition(0, 335);
		game->SetCamPos(0, 0);
		tilemaps->Get(SCENE_2)->index = 0;
		break;
	case GAMESTATE_2_2:
		simon->SetState(IDLE);
		simon->SetPosition(3115, 143);
		game->SetCamPos(3056, 0);
		tilemaps->Get(SCENE_2)->index = 1;
		break;
	case GAMESTATE_2_2_1:
		simon->SetState(STAIR_UP);
		simon->SetPosition(3172, 370);
		game->SetCamPos(3056, 0);
		tilemaps->Get(SCENE_2)->index = 1;
		break;
	case GAMESTATE_2_2_2:
		simon->SetState(STAIR_UP);
		simon->SetPosition(3812, 370);
		game->SetCamPos(3056, 0);
		tilemaps->Get(SCENE_2)->index = 1;
		break;
	case GAMESTATE_2_3:
		simon->SetState(IDLE);
		simon->SetPosition(4139, 143);
		game->SetCamPos(4079, 0);
		tilemaps->Get(SCENE_2)->index = 2;
		break;
	case GAMESTATE_3_1:
		simon->SetState(STAIR_DOWN);
		simon->SetPosition(100, 48);
		simon->SetN(1);
		game->SetCamPos(0, 0);
		tilemaps->Get(SCENE_3)->index = 0;
		break;
	case GAMESTATE_3_2:
		simon->SetState(STAIR_DOWN);
		simon->SetPosition(740, 48);
		simon->SetN(1);
		game->SetCamPos(0, 0);
		tilemaps->Get(SCENE_3)->index = 0;
		break;
	default:
		break;
	}
}

void SceneManager::ResetGame()
{
	isGameReset = true; // flag variable for reset time in Player::Update()

	isBossFighting = false;
	/*boss->SetState(BOSS_INACTIVE);*/
	simon->SetHP(16);
	simon->SetSubWeapon("");
	simon->GetWeapon()->SetState(MAGIC_WHIP);

	/*boss = new Boss();*/
	/*boss->SetState(BOSS_INACTIVE);*/

	int curIndex;

	switch (IDScene)
	{
	case SCENE_1:
		Init(SCENE_1);
		break;
	case SCENE_2:
		curIndex = tilemaps->Get(SCENE_2)->index;

		Init(SCENE_2);

		if (curIndex == 0)
			SetGameState(GAMESTATE_2_1);
		else if (curIndex == 1)
			SetGameState(GAMESTATE_2_2);
		else
		{
			SetGameState(GAMESTATE_2_3);
			isBossFighting = false;
		}
		break;
	case SCENE_3:
		Init(SCENE_2);
		SetGameState(GAMESTATE_2_2);
		break;
	default:
		break;
	}
}

void SceneManager::CrossEffect()
{
	if (simon->isGotCrossItem == true)
	{
		simon->isGotCrossItem = false;
		crossEffectTimer->Start();

		for (UINT i = 0; i < listObjects.size(); i++)
		{
			// Cross ch? tác d?ng v?i các object n?m trong viewport
			if (IsInViewport(listObjects[i]) == false)
				continue;

			/*if (dynamic_cast<Zombie*>(listObjects[i]) && listObjects[i]->GetState() == ZOMBIE_ACTIVE)
			{
				auto zombie = dynamic_cast<Zombie*>(listObjects[i]);
				zombie->SetState(ZOMBIE_DESTROYED);
			}
			else if (dynamic_cast<BlackLeopard*>(listObjects[i]) && listObjects[i]->GetState() == BLACK_LEOPARD_ACTIVE)
			{
				auto leopard = dynamic_cast<BlackLeopard*>(listObjects[i]);
				leopard->SetState(BLACK_LEOPARD_DESTROYED);
			}
			else if (dynamic_cast<VampireBat*>(listObjects[i]) && listObjects[i]->GetState() == VAMPIRE_BAT_ACTIVE)
			{
				auto bat = dynamic_cast<VampireBat*>(listObjects[i]);
				bat->SetState(VAMPIRE_BAT_DESTROYED);
			}
			else if (dynamic_cast<FishMan*>(listObjects[i]) && listObjects[i]->GetState() == FISHMAN_ACTIVE)
			{
				auto fishman = dynamic_cast<FishMan*>(listObjects[i]);
				fishman->SetState(FISHMAN_DESTROYED);
			}*/
		}
	}
}

void SceneManager::DoubleShotEffect()
{
	if (simon->isGotDoubleShotItem == true)
	{
		simon->isGotDoubleShotItem = false;
		/*doubleShotTimer->Start();*/
	}
}

void SceneManager::TripleShotEffect()
{
	if (simon->isGotTripleShotItem == true)
	{
		simon->isGotTripleShotItem = false;
		/*tripleShotTimer->Start();*/
	}
}

void SceneManager::Simon_Update(DWORD dt)
{
	if (simon->GetState() == DEAD)
	{
		if (isSimonDead == false)
		{
			isSimonDead = true;
			/*simonDeadTimer->Start();*/
		}

		return;
	}

	vector<LPGAMEOBJECT> coObjects;

	for (auto obj : listObjects)
	{
		if (dynamic_cast<Ground*>(obj))
				coObjects.push_back(obj);
		//if (dynamic_cast<Door*>(obj) || dynamic_cast<Ground*>(obj) ||
		//	dynamic_cast<ChangeSceneObject*>(obj) || dynamic_cast<Water*>(obj) || dynamic_cast<Candle*>(obj))
		//	coObjects.push_back(obj);
		//else if (dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL)
		//	coObjects.push_back(obj);
		//else if (simon->isAutoWalk == false) // n?u simon auto-walk s? không xét va ch?m v?i enemy
		//{
		//	if (dynamic_cast<FireBall*>(obj) && obj->IsEnable() == true)
		//		coObjects.push_back(obj);
		//	else if (dynamic_cast<Zombie*>(obj) && obj->GetState() == ZOMBIE_ACTIVE ||
		//		dynamic_cast<BlackLeopard*>(obj) && obj->GetState() == BLACK_LEOPARD_ACTIVE ||
		//		dynamic_cast<VampireBat*>(obj) && obj->GetState() == VAMPIRE_BAT_ACTIVE ||
		//		dynamic_cast<Boss*>(obj) && obj->GetState() == BOSS_ACTIVE)
		//		coObjects.push_back(obj);
		//	else if (dynamic_cast<FishMan*>(obj) && (obj->GetState() == FISHMAN_ACTIVE || obj->GetState() == FISHMAN_JUMP))
		//		coObjects.push_back(obj);
		//}
	}

	simon->Update(dt, &coObjects);
	simon->CheckCollisionWithItem(&listItems);
	simon->CheckCollisionWithEnemyActiveArea(&listObjects);
}

void SceneManager::Weapon_Update(DWORD dt, int index)
{
	if (simon->GetSubWeapon() == STOP_WATCH_SUB)
		return;

	/*if (subweaponList[index]->IsEnable() == false)
	{
		subweaponList[index]->SetTargetTypeHit("");
		return;
	}*/

	vector<LPGAMEOBJECT> coObjects;
	coObjects.push_back(simon); // dùng ?? xét va ch?m c?a Simon v?i boomerang

	/*if (isBossFighting == true && boss->GetState() == BOSS_ACTIVE && subweaponList[index]->GetTargetTypeHit() != BOSS)
		coObjects.push_back(boss);

	for (auto obj : listObjects)
	{
		if (dynamic_cast<Candle*>(obj) || dynamic_cast<Ground*>(obj) || dynamic_cast<FireBall*>(obj))
			coObjects.push_back(obj);
		else if (dynamic_cast<Zombie*>(obj) && obj->GetState() == ZOMBIE_ACTIVE ||
			dynamic_cast<VampireBat*>(obj) && obj->GetState() == BLACK_LEOPARD_ACTIVE)
			coObjects.push_back(obj);
		else if (dynamic_cast<BlackLeopard*>(obj) &&
			(obj->GetState() == BLACK_LEOPARD_ACTIVE || obj->GetState() == BLACK_LEOPARD_IDLE || obj->GetState() == BLACK_LEOPARD_JUMP))
			coObjects.push_back(obj);
		else if (dynamic_cast<FishMan*>(obj) &&
			(obj->GetState() == FISHMAN_ACTIVE || obj->GetState() == FISHMAN_JUMP || obj->GetState() == FISHMAN_HIT))
			coObjects.push_back(obj);
	}*/

	/*subweaponList[index]->Update(dt, &coObjects);*/
}

void SceneManager::Item_Update(DWORD dt, LPGAMEOBJECT& item)
{
	if (item->IsEnable() == true)
	{
		vector<LPGAMEOBJECT> coObjects;

		for (auto obj : listObjects)
		{
			/*if (dynamic_cast<Ground*>(obj) || (dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL))
				coObjects.push_back(obj);*/
		}

		item->Update(dt, &coObjects);
	}
}

//void SceneManager::Zombie_Update(DWORD dt, LPGAMEOBJECT& object)
//{
//	if (crossEffectTimer->IsTimeUp() == true && object->GetState() != ZOMBIE_INACTIVE)
//	{
//		auto zombie = dynamic_cast<Zombie*>(object);
//
//		if (zombie->isSettedPosition == false)
//		{
//			zombie->isSettedPosition = true;
//
//			float simon_x, simon_y;
//			simon->GetPosition(simon_x, simon_y);
//
//			int nx = zombie->GetEntryPosition().x < simon_x ? 1 : -1;
//			zombie->SetN(nx);
//
//			// C?n random m?t kho?ng nh? ?? tránh vi?c các zombie spawn cùng lúc, t?i cùng m?t v? trí
//			int randomDistance = rand() % 20;
//
//			float x, y;
//			y = zombie->GetEntryPosition().y;
//			if (nx == -1)
//				x = game->GetCamPos().x + SCREEN_WIDTH - (ENEMY_DEFAULT_BBOX_WIDTH + randomDistance);
//			else
//				x = game->GetCamPos().x + (ENEMY_DEFAULT_BBOX_WIDTH + randomDistance);
//
//			zombie->SetPosition(x, y);
//			zombie->SetState(ZOMBIE_ACTIVE);
//		}
//
//		vector<LPGAMEOBJECT> coObjects;
//
//		for (auto obj : listObjects)
//		{
//			if (dynamic_cast<Ground*>(obj) || (dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL))
//				coObjects.push_back(obj);
//		}
//
//		object->SetStopMovement(stopWatchMoment);
//		object->Update(dt, &coObjects);
//	}
//
//}
//
//void SceneManager::BlackLeopard_Update(DWORD dt, LPGAMEOBJECT& object)
//{
//	BlackLeopard* leopard = dynamic_cast<BlackLeopard*>(object);
//
//	if (leopard->GetState() == BLACK_LEOPARD_INACTIVE)
//	{
//		if (leopard->IsAbleToActivate() == true && IsInViewport(leopard) == true
//			&& abs(simon->x - leopard->GetEntryPosition().x) > BLACK_LEOPARD_ACTIVE_BBOX_WIDTH)
//		{
//			int nx = leopard->GetEntryPosition().x < simon->x ? 1 : -1;
//			leopard->SetN(nx);
//
//			leopard->SetState(BLACK_LEOPARD_IDLE);
//		}
//	}
//	else
//	{
//		vector<LPGAMEOBJECT> coObjects;
//
//		for (auto obj : listObjects)
//		{
//			if (dynamic_cast<Ground*>(obj) || (dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL))
//				coObjects.push_back(obj);
//		}
//
//		object->SetStopMovement(stopWatchMoment);
//		object->Update(dt, &coObjects);
//	}
//}
//
//void SceneManager::VampireBat_Update(DWORD dt, LPGAMEOBJECT& object)
//{
//	if (crossEffectTimer->IsTimeUp() == true && object->GetState() != VAMPIRE_BAT_INACTIVE)
//	{
//		auto bat = dynamic_cast<VampireBat*>(object);
//
//		if (bat->isSettedPosition == false)
//		{
//			bat->isSettedPosition = true;
//
//			// set random h??ng cho d?i
//			int listNx[2] = { -1, 1 };
//			int rndIndex = rand() % 2;
//			bat->SetN(listNx[rndIndex]);
//
//			// set v? trí cho d?i
//			// d?i bay ngang t?m simon, t? phía cu?i c?a 2 ??u màn hình)
//			float bx, by;
//			int randomDistance = rand() % 30;
//
//			by = simon->y + (rand() % SIMON_BBOX_HEIGHT);
//
//			if (bat->GetN() == -1)
//				bx = game->GetCamPos().x + SCREEN_WIDTH - (ENEMY_DEFAULT_BBOX_WIDTH - randomDistance);
//			else
//				bx = game->GetCamPos().x + (ENEMY_DEFAULT_BBOX_WIDTH - randomDistance);
//
//			bat->SetPosition(bx, by);
//			bat->SetState(VAMPIRE_BAT_ACTIVE);
//		}
//
//		bat->SetStopMovement(stopWatchMoment);
//		bat->Update(dt, NULL);
//	}
//}
//
//void SceneManager::FishMan_Update(DWORD dt, LPGAMEOBJECT& object)
//{
//	auto fishman = dynamic_cast<FishMan*>(object);
//
//	if (fishman->GetState() != FISHMAN_INACTIVE)
//	{
//		if (fishman->GetState() == FISHMAN_ACTIVE && fishman->isSettedPosition == true &&
//			GetTickCount() - fishman->GetLastTimeShoot() >= fishman->GetDeltaTimeToShoot())
//		{
//			fishman->SetState(FISHMAN_HIT);
//
//			// T?o fireball
//			float fx, fy, nx;
//
//			fishman->GetPosition(fx, fy);
//			nx = fishman->GetN();
//
//			auto fireball = new FireBall();
//			fireball->SetPosition(fx + 5, fy + 10);
//			fireball->SetN(nx);
//			fireball->SetState(FIREBALL);
//			fireball->SetEnable(true);
//
//			grid->Add(fireball);
//
//			// ??t h??ng quay m?t c?a Fishman sau khi b?n (quay v? phía simon)
//			float sx, sy;
//			simon->GetPosition(sx, sy);
//
//			if (fx < sx) fishman->SetNxAfterShoot(1);
//			else fishman->SetNxAfterShoot(-1);
//		}
//		else
//		{
//			if (crossEffectTimer->IsTimeUp() == true && fishman->isSettedPosition == false)
//			{
//				fishman->isSettedPosition = true;
//
//				// Set v? trí cho fishman d?a vào v? trí c?a Simon
//				float simon_x, simon_y;
//				simon->GetPosition(simon_x, simon_y);
//
//				int nx = simon_x > fishman->GetEntryPosition().x ? 1 : -1;
//				float distance = 50 + rand() % 150;
//
//				float x = simon_x - nx * distance;
//				float y = fishman->GetEntryPosition().y;
//
//				fishman->SetN(nx);
//				fishman->SetPosition(x, y);
//
//				fishman->SetState(FISHMAN_JUMP);
//
//				// Thêm bubbles vào water ?? render b?t n??c
//				water->AddBubbles(x, y);
//			}
//
//			vector<LPGAMEOBJECT> coObjects;
//
//			for (auto obj : listObjects)
//			{
//				if ((dynamic_cast<BreakWall*>(obj) && obj->GetState() == NORMAL) ||
//					dynamic_cast<Ground*>(obj) || dynamic_cast<Water*>(obj))
//					coObjects.push_back(obj);
//			}
//
//			fishman->SetStopMovement(stopWatchMoment);
//			fishman->Update(dt, &coObjects);
//		}
//	}
//}
//
//void SceneManager::Boss_Update(DWORD dt, LPGAMEOBJECT& object)
//{
//	if (object->GetState() == BOSS_INACTIVE)
//		return;
//
//	boss = dynamic_cast<Boss*>(object);
//
//	// Passing simon's position for boss movement
//	float sx, sy;
//	simon->GetPosition(sx, sy);
//	boss->SetSimonPosition(sx, sy);
//
//	D3DXVECTOR2 camPosition = game->GetCamPos();
//	boss->SetCamPos(camPosition.x, camPosition.y);
//
//	boss->Update(dt);
//}

