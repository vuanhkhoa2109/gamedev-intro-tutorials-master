#include "weapon.h"
#include "LoadResource.h"
#include "Candle.h"


Weapon::Weapon()
{
	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsWeapon = loadResourceFile->GetAnimations("resources\\weapons\\weapons_ani.xml");
	for each (string animation in animationsWeapon)
	{
		AddAnimation(animation);
	}

	state = LONG_CHAIN;
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isLastFame)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<Candle*>(obj))
			{
				Candle* e = dynamic_cast<Candle*> (obj);

				if (this->AABBx(e) == true)
				{
					e->SetState(CANDLE_DESTROYED);
					e->isLastFame = false;
				}
			}
			/*

			else if (dynamic_cast<Zombie*>(obj))
			{
				Zombie* e = dynamic_cast<Zombie*> (obj);

				if (this->AABBx(e) == true)
				{
					e->vx = 0;
					e->SetState(ZOMBIE_DESTROYED);
					e->isLastFame = false;
				}
			}

			else if (dynamic_cast<BlackLeopard*>(obj))
			{
				BlackLeopard* e = dynamic_cast<BlackLeopard*> (obj);

				if (this->AABBx(e) == true)
				{
					e->vx = 0;
					e->SetState(BLACK_LEOPARD_DESTROYED);
					e->isLastFame = false;
				}
			}

			else if (dynamic_cast<VampireBat*>(obj))
			{
				VampireBat* e = dynamic_cast<VampireBat*> (obj);

				if (this->AABBx(e) == true)
				{
					e->vx = 0;
					e->SetState(VAMPIRE_BAT_DESTROYED);
					e->isLastFame = false;
				}
			}

			else if (dynamic_cast<FishMan*>(obj))
			{
				FishMan* e = dynamic_cast<FishMan*> (obj);

				if (this->AABBx(e) == true)
				{
					e->vx = 0;
					e->SetState(FISHMAN_DESTROYED);
					e->isLastFame = false;
				}
			}

			else if (dynamic_cast<FireBall*>(obj))
			{
				FireBall* e = dynamic_cast<FireBall*>(obj);

				if (this->AABBx(e) == true)
				{
					GetCoordinateObject(obj);
					e->vx = 0;
					e->SetEnable(false);
					e->isLastFame = false;
				}
			}

			else if (dynamic_cast<BreakWall*>(obj))
			{
				BreakWall* e = dynamic_cast<BreakWall*>(obj);

				if (this->AABBx(e) == true)
				{
					e->SetState(BREAK);
					e->isLastFame = false;
				}
			}

			else if (dynamic_cast<Boss*>(obj))
			{
				Boss* e = dynamic_cast<Boss*> (obj);

				if (this->AABBx(e) == true)
				{
					GetCoordinateObject(obj);
					e->LoseHP(2);
				}
			}*/
		}
	}
	this->isLastFame = false;
}

void Weapon::Render()
{
	RenderSpark();
	animations[state]->Render(nx, x, y);
	this->isLastFame = this->animations[state]->IsCompleted();
}

void Weapon::RenderSpark()
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

void Weapon::GetCoordinateObject(LPGAMEOBJECT obj)
{
	float l, t, r, b;
	obj->GetBoundingBox(l, t, r, b);

	sparkCoord.push_back({ l, t });
}

void Weapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y + 15;
	bottom = top + WHIP_BBOX_HEIGHT;
	if (nx < 0)
	{
		if (state != LONG_CHAIN)
			left = x + 50;
		else left = x + 20;
	}
	else if (nx > 0)
	{
		if (state != LONG_CHAIN)
			left = (240 - 50) - WHIP_BBOX_WIDTH + x;
		else left = (240 - 20) - LONG_CHAIN_BBOX_WIDTH + x;
	}

	if (state != LONG_CHAIN)
		right = left + WHIP_BBOX_WIDTH;
	else  right = left + LONG_CHAIN_BBOX_WIDTH;
}

void Weapon::SetWeaponPosition(D3DXVECTOR3 simonPositon, bool sitting)
{
	simonPositon.x -= 90.0f;
	if (sitting)
		simonPositon.y += 15.0f;

	SetPosition(simonPositon.x, simonPositon.y);
}
