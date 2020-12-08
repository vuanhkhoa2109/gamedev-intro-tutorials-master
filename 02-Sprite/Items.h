#pragma once
#include "GameObject.h"
#include "LoadResource.h"

class Items : public GameObject
{
	DWORD timeAppear;   // th?i gian b?t ??u xu?t hi?n c?a item, dùng ?? xét cho item t? hu?
	float velocityVariation_x;	// bi?n thiên v?n t?c theo chi?u x ?? cho smallheart bay l?o ??o

public:

	Items();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(string state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);

	void SetItem(string nameItem);
};