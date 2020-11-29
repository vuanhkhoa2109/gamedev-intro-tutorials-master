#pragma once
#include "GameObject.h"

class Stair : public GameObject
{
public:
	Stair();
	~Stair();

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};