#pragma once
#include"GameObject.h"
class HiddenObject :public GameObject
{
private:
	float width;
	float height;
public:
	float GetWidth() { return width; };
	float GetHeight() { return height; }
	void SetSize(float width, float height) { this->height = height, this->width = width; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
};

