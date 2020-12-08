#pragma once
#include "Enemy.h"
#include "LoadResource.h"

class Zombie : public Enemy
{

public:
	Zombie();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void SetState(string state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void LoseHP(int x);
};

