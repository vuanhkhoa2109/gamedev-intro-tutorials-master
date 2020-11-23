#include "GetHiddenMoneyObject.h"

void GetHiddenMoneyObject::Render()
{
	RenderBoundingBox();
}

void GetHiddenMoneyObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + this->GetWidth();
	b = y + this->GetHeight();
}

void GetHiddenMoneyObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject) 
{
	GameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.1f;
		if (ny != 0)
		{
			vx = 0;
			vy = 0;
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
