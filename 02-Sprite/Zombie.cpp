
#include "Zombie.h"
#include "LoadResource.h"



Zombie::Zombie()
{
	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsZombie = loadResourceFile->GetAnimations("resources\\zombie\\zombie_ani.xml");

	for each (string animation in animationsZombie)
	{
		AddAnimation(animation);
	}

	vector<string> animationsEffect = loadResourceFile->GetAnimations("resources\\effect\\effect_ani.xml");
	for each (string animation in animationsEffect)
	{
		AddAnimation(animation);
	}

	HP = 1;
	score = 100;
	attack = 2;
	respawnWaitingTime = 5000;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (state == ZOMBIE_INACTIVE)
		return;

	if (state == ZOMBIE_DESTROYED && animations[state]->IsOver(EFFECT_ANI_TIME_DELAY) == true)
	{
		SetState(ZOMBIE_INACTIVE);
		return;
	}

	if (stopMovement == true)
		return;

	Enemy::Update(dt);

	// Check collision between zombie and ground (falling on ground)
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		vy += ZOMBIE_GRAVITY * dt;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0 && ny == 0)
		{
			this->nx *= -1;
			this->vx *= -1;
		}
		else if (ny == -1.0f)
		{
			vy = 0;
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Zombie::Render()
{
	if (state != ZOMBIE_INACTIVE)
		animations[state]->Render(nx, x, y);
}

void Zombie::SetState(string state)
{
	Enemy::SetState(state);

	if (state == ZOMBIE_ACTIVE)
	{
		if (nx > 0) vx = ZOMBIE_WALKING_SPEED;
		else vx = -ZOMBIE_WALKING_SPEED;
		vy = 0;
		isDroppedItem = false;
		respawnTime_Start = 0;
		isRespawnWaiting = false;
	}
	else if (state == ZOMBIE_DESTROYED)
	{
		vx = 0;
		animations[state]->SetAniStartTime(GetTickCount());
	}
	else if (state == ZOMBIE_INACTIVE)
	{
		x = entryPosition.x;
		y = entryPosition.y;
		vx = 0;
		isSettedPosition = false;
		StartRespawnTimeCounter();
	}
}

void Zombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 11;  // (10/32)
	top = y + 2; // (60,64)
	right = left + ZOMBIE_BBOX_WIDTH;
	bottom = top + ZOMBIE_BBOX_HEIGHT;
}

void Zombie::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = entryPosition.x - ZOMBIE_ACTIVE_BBOX_WIDTH;
	right = entryPosition.x + ZOMBIE_ACTIVE_BBOX_WIDTH;
	top = entryPosition.y - ZOMBIE_ACTIVE_BBOX_HEIGHT;
	bottom = entryPosition.y + ZOMBIE_ACTIVE_BBOX_HEIGHT;
}

void Zombie::LoseHP(int x)
{
	Enemy::LoseHP(x);

	if (HP == 0)
		SetState(ZOMBIE_DESTROYED);
}