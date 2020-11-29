#pragma once

#include "GameObject.h"

class FireBall : public GameObject
{
public:
	FireBall();
	~FireBall();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

	void SetState(string state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
