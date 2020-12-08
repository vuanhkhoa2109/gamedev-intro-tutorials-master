#pragma once
#include "GameObject.h"
#include "LoadResource.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

class Ground : public GameObject
{
public:

	Ground();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(string state);
};