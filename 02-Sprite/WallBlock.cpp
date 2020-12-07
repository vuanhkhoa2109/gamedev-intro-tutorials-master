#include "WallBlock.h"

WallBlock::WallBlock()
{
	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsBreakWall = loadResourceFile->GetAnimations("resources\\break_wall\\break_wall_ani.xml");
	for each (string animation in animationsBreakWall)
	{
		AddAnimation(animation);
	}

	SetState("WALL_BLOCK");
}

void WallBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	GameObject::Update(dt);
	vy += WALLBLOCKS_GRAVITY * dt;

	x += dx;
	y += dy;
}

void WallBlock::Render()
{
	animations[state]->Render(nx, x, y);
}

WallBlocks::WallBlocks(float x, float y)
{
	WallBlock* block;

	for (int i = 1; i <= 4; i++)
	{
		block = new WallBlock();
		block->SetPosition(x, y);

		float vx = (float)(-100 + rand() % 200) / 1000;
		float vy = (float)(-100 + rand() % 200) / 1000;
		block->SetSpeed(vx, vy);

		blocks.push_back(block);
	}
}

WallBlocks::~WallBlocks()
{
	for (int i = 0; i < 4; i++)
		delete(blocks[i]);

	blocks.clear();
}

void WallBlocks::Update(DWORD dt)
{
	for (auto block : blocks)
		block->Update(dt);
}

void WallBlocks::Render()
{
	for (auto block : blocks)
		block->Render();
}

