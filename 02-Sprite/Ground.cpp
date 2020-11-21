#include "Ground.h"
#include "LoadResource.h"

Ground::Ground()
{
	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsGround = loadResourceFile->GetAnimations("resources\\ground\\ground_ani.xml");
	for each (string animation in animationsGround)
	{
		AddAnimation(animation);
	}
}

void Ground::Render()
{
	animations[state]->Render(-1, x, y);
}

void Ground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void Ground::SetState(string state)
{
	GameObject::SetState(state);
}
