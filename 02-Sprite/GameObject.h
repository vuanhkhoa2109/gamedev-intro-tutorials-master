#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <unordered_map>
#include <d3dx9.h>
#include <algorithm>

#include "Sprites.h"
#include "Textures.h"
#include "LoadResource.h"
#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "Sprites.h"
#include "Const.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class GameObject;
typedef GameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};



class GameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	string state;

	bool isLastFame = false;
	bool isEnable;
	string nameItem; // id cua object chua item (string empty = ko co item)
	string type;

	bool stopMovement = false;
	bool isDroppedItem = false;

	D3DXVECTOR2 entryPosition; // ??a enemy v? v? trí entry sau th?i gian respawn

	DWORD dt;


	// vector<LPANIMATION> animations;
	unordered_map<string, LPANIMATION> animations;

public:
	GameObject();

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void SetN(int nx) { this->nx = nx; }
	void SetIdItem(string nameItem) { this->nameItem = nameItem; }
	void SetEnable(bool enable) { this->isEnable = enable; }
	void SetEntryPosition(float x, float y) { entryPosition.x = x; entryPosition.y = y; }
	void SetType(string type) { this->type = type; }
	void SetIsDroppedItem(bool x) { this->isDroppedItem = x; }
	void SetStopMovement(bool x) { this->stopMovement = x; }

	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	int GetN() { return nx; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	string GetState() { return this->state; }
	string GetType() { return type; }
	bool IsEnable() { return this->isEnable; }
	bool IsDroppedItem() { return this->isDroppedItem; }
	D3DXVECTOR2 GetEntryPosition() { return this->entryPosition; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);

	bool AABBx(LPGAMEOBJECT coO);

	void AddAnimation(string aniId);

	virtual void GetBoundingBox(float& left, float& top, float& width, float& height) = 0;
	// L?y boundingbox vùng va ch?m v?i simon ?? khi?n enemy active
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom) {};

	void RenderBoundingBox();
	void RenderActiveBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(string state) { this->state = state; }

	~GameObject();
};

