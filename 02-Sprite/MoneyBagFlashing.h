#pragma once
#include "Items.h"

class MoneyBagFlashing : public Items
{
public:
	MoneyBagFlashing() {
		state = MONEY_BAG_FLASHING;
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

