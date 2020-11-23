#pragma once
#include "HiddenObject.h"
class GetHiddenMoneyObject : public HiddenObject
{
private:
	bool isTouched = false;
public:
	void setTouch(bool touch) {
		this->isTouched = touch;
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

