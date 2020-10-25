#pragma once
#include "GameObject.h"
#include "debug.h"
class Weapon :
	public GameObject
{
	vector<vector<float>> sparkCoord; // vector l?u to? ?? ?? render spark khi subweapon tr�ng m?c ti�u
	Animation* spark = Animations::GetInstance()->Get("spark");
	int startTimeRenderSpark = 0;
public:
	Weapon();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	void RenderSpark();
	void GetCoordinateObject(LPGAMEOBJECT obj);			// L?y to? ?? c?a object ?? l?u v�o sparkC

	void SetWeaponPosition(D3DXVECTOR3 simonPositon, bool sitting);
};

