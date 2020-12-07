#pragma once

#include "GameObject.h"

class WallBlock : public GameObject
{
public:
	WallBlock();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

typedef WallBlock* LPWALLBLOCK;

class WallBlocks
{
	DWORD startTime = 0;
	vector<LPWALLBLOCK> blocks;

public:
	WallBlocks(float x, float y);
	~WallBlocks();

	void Update(DWORD dt);
	void Render();

	DWORD GetStartTimeRender() { return startTime; }
	void SetStartTimeRender(DWORD x) { startTime = x; }
};

