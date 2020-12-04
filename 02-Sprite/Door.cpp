#include "Door.h"

Door::Door() : GameObject()
{
	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsDoor = loadResourceFile->GetAnimations("resources\\door\\door_ani.xml");
	for each (string animation in animationsDoor)
	{
		AddAnimation(animation);
	}

	vector<string> animationsGate = loadResourceFile->GetAnimations("resources\\door\\gate_ani.xml");
	for each (string animation in animationsGate)
	{
		AddAnimation(animation);
	}
}

Door::~Door()
{
}

void Door::Render()
{
	if (state == DOOR_2_OPEN && animations[state]->IsOver(5000) == true)
	{
		state = DOOR_2_IDLE;
	}

	animations[state]->Render(-1, x, y);
}

void Door::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == DOOR_1)
	{
		l = 1376;
		t = 272;
		r = l + DOOR_BBOX_WIDTH;
		b = t + DOOR_BBOX_HEIGHT;
	}

	else if (state == DOOR_2_IDLE || state == DOOR_2_OPEN)
	{
		l = x - 16;
		t = y;
		r = l + DOOR_BBOX_WIDTH;
		b = t + DOOR_BBOX_HEIGHT;
	}
}
