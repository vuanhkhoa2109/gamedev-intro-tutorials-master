#include "Stair.h"

Stair::Stair()
{
	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsStair = loadResourceFile->GetAnimations("resources\\stair\\stair_ani.xml");
	for each (string animation in animationsStair)
	{
		AddAnimation(animation);
	}
}


Stair::~Stair()
{
}


void Stair::Render()
{
	animations[state]->Render(-1, x, y);
}

void Stair::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + STAIR_BBOX_WIDTH;
	b = t + STAIR_BBOX_HEIGHT;
}

