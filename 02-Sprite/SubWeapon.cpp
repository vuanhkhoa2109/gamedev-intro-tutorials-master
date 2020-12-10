#include "SubWeapon.h"

SubWeapon::SubWeapon()
{
	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsSubWeapons = loadResourceFile->GetAnimations("resources\\sub_weapons\\sub_weapons_ani.xml");
	for each (string animation in animationsSubWeapons)
	{
		AddAnimation(animation);
	}

	state = "";
}

void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isHolyWaterShattered == true &&
		GetTickCount() - holyWaterShatteredCounter > WEAPONS_HOLY_WATER_TIME_EFFECT)
	{
		isHolyWaterShattered = false;
		holyWaterShatteredCounter = 0;
		this->isEnable = false;
		return;
	}

	GameObject::Update(dt);

	if (state == AXE_SUB)
	{
		vy += WEAPONS_AXE_GRAVITY * dt;
	}

	else if (state == HOLY_WATER_SUB)
	{
		vy += WEAPONS_HOLY_WATER_GRAVITY * dt;
	}

	else if (state == BOOMERANG_SUB)
	{
		if (this->nx > 0) vx -= WEAPONS_BOOMERANG_TURNBACK_SPEED;
		else vx += WEAPONS_BOOMERANG_TURNBACK_SPEED;
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		// ki?m tra va ch?m v?i object
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Candle*>(e->obj))
			{
				Candle* candle = dynamic_cast<Candle*>(e->obj);
				candle->SetState(CANDLE_DESTROYED);

				targetTypeHit = CANDLE;
				GetCoordinateObject(e->obj);

				if (state == DAGGER_SUB || state == AXE_SUB || state == BOOMERANG_SUB)
				{
					this->isEnable = false;
				}
				else
				{
					x += dx;
					y += dy;
				}
			}

			else if (dynamic_cast<FireBall*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
				if (state == BOOMERANG_SUB)
					this->isEnable = false;
			}

			else if (dynamic_cast<Zombie*>(e->obj))
			{
				Zombie* zombie = dynamic_cast<Zombie*>(e->obj);
				zombie->SetState(ZOMBIE_DESTROYED);

				targetTypeHit = ZOMBIE;

				if (state == DAGGER_SUB || state == AXE_SUB || state == BOOMERANG_SUB)
				{
					this->isEnable = false;
				}
				else
				{
					x += dx;
					y += dy;
				}
			}
			else if (dynamic_cast<BlackLeopard*>(e->obj))
			{
				BlackLeopard* blackLeopard = dynamic_cast<BlackLeopard*>(e->obj);
				blackLeopard->SetState(BLACK_LEOPARD_DESTROYED);

				targetTypeHit = BLACK_LEOPARD;

				if (state == DAGGER_SUB || state == AXE_SUB || state == BOOMERANG_SUB)
					this->isEnable = false;
				else
				{
					x += dx;
					y += dy;
				}
			}
			else if (dynamic_cast<VampireBat*>(e->obj))
			{
				VampireBat* vampirebat = dynamic_cast<VampireBat*>(e->obj);
				vampirebat->SetState(VAMPIRE_BAT_DESTROYED);

				targetTypeHit = VAMPIRE_BAT;

				if (state == DAGGER_SUB || state == AXE_SUB || state == BOOMERANG_SUB)
					this->isEnable = false;
				else
				{
					x += dx;
					y += dy;
				}
			}
			else if (dynamic_cast<FishMan*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
				if (state == BOOMERANG_SUB)
					this->isEnable = false;
			}
			else if (dynamic_cast<Boss*>(e->obj))
			{
				Boss* boss = dynamic_cast<Boss*>(e->obj);
				boss->LoseHP(5);
				targetTypeHit = FISHMAN;
				GetCoordinateObject(e->obj);

				if (state == DAGGER_SUB || state == AXE_SUB || state == BOOMERANG_SUB)
					this->isEnable = false;
				else
				{
					x += dx;
					y += dy;
				}
			}
			else if (dynamic_cast<Ground*>(e->obj))
			{
				if (state == HOLY_WATER_SUB && e->ny == -1)
					SetState(HOLY_WATER_SHATTERED_SUB);

				x += dx;
				y += dy;
			}
			else if (dynamic_cast<Simon*>(e->obj))
			{
				if (state == BOOMERANG_SUB)
					this->isEnable = false;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void SubWeapon::Render()
{
	RenderSpark();

	if (this->isEnable == true && state != STOP_WATCH_SUB)
	{
		animations[state]->Render(nx, x, y);

	}
}

void SubWeapon::RenderSpark()
{
	if (sparkCoord.size() > 0)
	{
		if (startTimeRenderSpark == 0)
			startTimeRenderSpark = GetTickCount();
		else if (GetTickCount() - startTimeRenderSpark > SPARK_ANI_TIME_DELAY)
		{
			startTimeRenderSpark = 0;
			sparkCoord.clear();
		}

		for (auto coord : sparkCoord)
			spark->Render(-1, coord[0], coord[1]);
	}
}

void SubWeapon::SetState(string state)
{
	GameObject::SetState(state);

	if (state == STOP_WATCH_SUB)
	{
	}

	else if (state == DAGGER_SUB)
	{
		if (nx > 0) vx = WEAPONS_DAGGER_SPEED;
		else vx = -WEAPONS_DAGGER_SPEED;
		vy = 0;
	}

	else if (state == AXE_SUB)
	{
		if (nx > 0) vx = WEAPONS_AXE_SPEED_X;
		else vx = -WEAPONS_AXE_SPEED_X;
		vy = -WEAPONS_AXE_SPEED_Y;
	}

	else if (state == HOLY_WATER_SUB)
	{
		vx = nx * WEAPONS_HOLY_WATER_SPEED_X;
		vy = -WEAPONS_HOLY_WATER_SPEED_Y;
	}

	else if (state == BOOMERANG_SUB)
	{
		vx = nx * WEAPONS_BOOMERANG_SPEED;
		vy = 0;
	}

	else if (state == HOLY_WATER_SHATTERED_SUB)
	{
		vx = 0;
		vy = 0;
		StartHolyWaterEffect();
	}
}

void SubWeapon::GetCoordinateObject(LPGAMEOBJECT obj)
{
	float l, t, r, b;
	obj->GetBoundingBox(l, t, r, b);

	sparkCoord.push_back({ l, t });
}

void SubWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (state == STOP_WATCH_SUB)
	{
		right = left;
		bottom = top;
	}

	else if (state == DAGGER_SUB)
	{
		right = left + WEAPONS_DAGGER_BBOX_WIDTH;
		bottom = top + WEAPONS_DAGGER_BBOX_HEIGHT;
	}

	else if (state == AXE_SUB)
	{
		right = left + WEAPONS_AXE_BBOX_WIDTH;
		bottom = top + WEAPONS_AXE_BBOX_HEIGHT;
	}

	else if (state == HOLY_WATER_SUB)
	{
		right = left + WEAPONS_HOLY_WATER_BBOX_WIDTH;
		bottom = top + WEAPONS_AXE_BBOX_HEIGHT;
	}

	else if (state == BOOMERANG_SUB)
	{
		right = left + WEAPONS_BOOMERANG_BBOX_WIDTH;
		bottom = top + WEAPONS_BOOMERANG_BBOX_HEIGHT;
	}

	else
	{
		right = left + WEAPONS_HOLY_WATER_BBOX_WIDTH;
		bottom = top + WEAPONS_AXE_BBOX_HEIGHT;
	}
}



