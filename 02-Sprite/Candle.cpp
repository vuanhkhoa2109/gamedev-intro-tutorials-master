#include "Candle.h"

Candle::Candle()
{
	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();
	vector<string> animationsCandle = loadResourceFile->GetAnimations("resources\\candle\\candle_ani.xml");
	for each (string animation in animationsCandle)
	{
		AddAnimation(animation);
	}

	vector<string> animationsEffect = loadResourceFile->GetAnimations("resources\\effect\\effect_ani.xml");
	for each (string animation in animationsEffect)
	{
		AddAnimation(animation);
	}
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == CANDLE_DESTROYED && isLastFame) 
	{
		this->isEnable = false;
	}
}

void Candle::Render()
{
	animations[state]->Render(1, x, y);
	this->isLastFame = animations[state]->IsCompleted();
}

void Candle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (state == LARGE_CANDLE)
	{
		right = left + LARGE_CANDLE_BBOX_WIDTH;
		bottom = top + LARGE_CANDLE_BBOX_HEIGHT;
	}

	else if (state == CANDLE)
	{
		right = left + CANDLE_BBOX_WIDTH;
		bottom = top + CANDLE_BBOX_HEIGHT;
	}
}

void Candle::SetState(string state)
{
	GameObject::SetState(state);
}
