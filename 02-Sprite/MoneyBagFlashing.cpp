#include "MoneyBagFlashing.h"

void MoneyBagFlashing::Render()
{
	RenderBoundingBox();
}

void MoneyBagFlashing::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	Items::GetBoundingBox(l, t, r, b);
}

void MoneyBagFlashing::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	Items::Update(dt);
}
