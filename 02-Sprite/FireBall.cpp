#include "FireBall.h"

FireBall::FireBall()
{

	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsFireBall = loadResourceFile->GetAnimations("resources\\fire_ball\\fire_ball_ani.xml");

	for each (string animation in animationsFireBall)
	{
		AddAnimation(animation);
	}

	SetState(FIREBALL);
}


FireBall::~FireBall()
{
}


void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	GameObject::Update(dt);
	x += dx;
}

void FireBall::Render()
{
	animations[state]->Render(nx, x, y);
}

void FireBall::SetState(string state)
{
	GameObject::SetState(state);

	if (state == FIREBALL)
	{
		if (nx == 1) vx = FIREBALL_SPEED;
		else vx = -FIREBALL_SPEED;
		vy = 0;
	}
}

void FireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}