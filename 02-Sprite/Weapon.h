#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "FireBall.h"
#include "FishMan.h"
#include "LoadResource.h"
#include "Candle.h"
#include "BreakWall.h"
#include "Boss.h"
#include "VampireBat.h"

class Weapon :
	public GameObject
{
	vector<vector<float>> sparkCoord;
	Animation* spark = Animations::GetInstance()->Get("spark");
	int startTimeRenderSpark = 0;
public:
	Weapon();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	void RenderSpark();
	void GetCoordinateObject(LPGAMEOBJECT obj);

	void SetWeaponPosition(D3DXVECTOR3 simonPositon, bool sitting);
};

