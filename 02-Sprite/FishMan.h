#pragma once

#include "Enemy.h"

class FishMan :public Enemy
{
	DWORD lastTimeShoot; // th?i gian k? t? lúc v?a b?n xong ??n l?n b?n ti?p theo
	DWORD deltaTimeToShoot; // kho?ng th?i gian k? t? lúc fishman xu?t hi?n ??n lúc b?n 
	int nxAfterShoot; // H??ng quay m?t sau khi b?n (?? luôn quay m?t v? phía Simon)

public:
	FishMan();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void SetState(string state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void LoseHP(int x);

	int GetLastTimeShoot() { return lastTimeShoot; }
	int GetDeltaTimeToShoot() { return deltaTimeToShoot; }

	void SetNxAfterShoot(int x) { nxAfterShoot = x; }
};