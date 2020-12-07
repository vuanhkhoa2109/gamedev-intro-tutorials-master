#pragma once
#include "GameObject.h"
#include "WallBlock.h"

class BreakWall : public GameObject
{
	bool isBreakToPieces = false;
	WallBlocks* blocks = NULL;

public:
	BreakWall();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();
	void SetState(string state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

