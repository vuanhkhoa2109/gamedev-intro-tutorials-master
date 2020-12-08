#pragma once

#include "Enemy.h"
#include "debug.h"

class Boss : public Enemy
{
	bool isFlyToTarget = false;
	bool isFlyToSimon = false;

	int idTarget = 0;
	D3DXVECTOR2 simonPostion;
	D3DXVECTOR2 cam;
	D3DXVECTOR2 target;

	int startTimeWaiting = 0;
	bool isStopWaiting = false;

	bool dropItem = false;

public:
	Boss();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void SetState(string state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void LoseHP(int x);

	D3DXVECTOR2 GetRandomSpot();
	void FlyToTarget(DWORD dt);
	void GetVelocity();

	void StartStopTimeCounter() { isStopWaiting = true; startTimeWaiting = GetTickCount(); }

	void SetSimonPosition(float sx, float sy) { simonPostion.x = sx; simonPostion.y = sy; }
	void SetCamPos(float camx, float camy) { cam.x = camx; cam.y = camx; }

	int GetIdTarget() { return idTarget; }

	bool DropItem() { return dropItem; }
};


