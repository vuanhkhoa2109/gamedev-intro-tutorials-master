#include "Items.h"
#include "LoadResource.h"

Items::Items()
{
	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsItems = loadResourceFile->GetAnimations("resources\\items\\items_ani.xml");
	for each (string animation in animationsItems)
	{
		AddAnimation(animation);
	}

	timeAppear = -1;
	vy = ITEM_FALLING_SPEED;
}

void Items::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (state != MAGIC_CRYSTAL)
	{
		if (timeAppear == -1)
			timeAppear = GetTickCount();
		else
		{
			DWORD now = GetTickCount();

			if (now - timeAppear > ITEM_TIME_DESTROYED)
			{
				isEnable = false;
				return;
			}
		}
	}


	GameObject::Update(dt);
	if (state == LARGE_HEART && vy != 0)
	{
		vx += velocityVariation_x;
		if (vx >= ITEM_FALLING_SPEED_X || vx <= -ITEM_FALLING_SPEED_X)
			velocityVariation_x *= -1; // ??i chi?u
	}

	if (state == MONEY_BAG_FLASHING && y == 304.0) {
		y -= 0.5f;	
	}
	else {
		// Check collision between item and ground (falling on ground)
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
	
		
}

void Items::Render()
{
	int alpha = 255;

	if (state != MAGIC_CRYSTAL && GetTickCount() - timeAppear > ITEM_TIME_DESTROYED / 2)
		alpha -= 100 * (rand() % 2);

	animations[state]->Render(-1, x, y, alpha);
}

void Items::SetState(string state)
{
	GameObject::SetState(state);

	if (state == SMALL_HEART)
	{
		velocityVariation_x = ITEM_FALLING_SPEED_X_VARIATION;
		vx = 0;
		vy = ITEM_SMALLHEART_FALLING_SPEED_Y;
	}
	else
	{
		vx = 0;
		vy = ITEM_FALLING_SPEED_Y;
	}
}

void Items::SetItem(string nameItem)
{
	state = nameItem;
}

void Items::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (state == STOP_WATCH)
	{
		right = left + 26;
		bottom = top + 28;
	}
	else if (state == DAGGER)
	{
		right = left + 32;
		bottom = top + 18;
	}
	else if (state == AXE)
	{
		right = left + 30;
		bottom = top + 28;
	}
	else if (state == HOLY_WATER)
	{
		right = left + 28;
		bottom = top + 28;
	}
	else if (state == BOOMERANG)
	{
		right = left + 30;
		bottom = top + 28;
	}
	else if (state == SMALL_HEART)
	{
		right = left + 16;
		bottom = top + 16;
	}
	else if (state == LARGE_HEART)
	{
		right = left + 24;
		bottom = top + 20;
	}
	else if (state == CROSS)
	{
		right = left + 32;
		bottom = top + 32;
	}
	else if (state == INVISIBILITY_POTION)
	{
		right = left + 29;
		bottom = top + 36;
	}
	else if (state == CHAIN)
	{
		right = left + 32;
		bottom = top + 32;
	}
	else if (state == MONEY_BAG_RED || state == MONEY_BAG_BLUE || state == MONEY_BAG_WHITE || state == MONEY_BAG_FLASHING)
	{
		right = left + 30;
		bottom = top + 30;
	}
	else if (state == DOUBLE_SHOT || state == TRIPLE_SHOT)
	{
		right = left + 28;
		bottom = top + 28;
	}
	else if (state == PORK_CHOP)
	{
		right = left + 32;
		bottom = top + 26;
	}
	else if (state == MAGIC_CRYSTAL)
	{
		right = left + 28;
		bottom = top + 32;
	}
	else
	{
		right = left;
		bottom = top;
	}
}

