#pragma once
#include "GameObject.h"

class SubWeapon : public GameObject
{
	bool isHolyWaterShattered = false;
	int holyWaterShatteredCounter = 0;

	string targetTypeHit = ""; // Lo?i m?c tiêu ?ánh trúng (dùng ?? ki?m tra máu c?a boss...)

	vector<vector<float>> sparkCoord; // vector l?u to? ?? ?? render spark khi subweapon trúng m?c tiêu
	Animation* spark = Animations::GetInstance()->Get("spark");
	int startTimeRenderSpark = 0;
public:
	SubWeapon();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void Render();
	void RenderSpark();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(string state);

	void StartHolyWaterEffect() { isHolyWaterShattered = true; holyWaterShatteredCounter = GetTickCount(); }


	string GetTargetTypeHit() { return targetTypeHit; }
	void SetTargetTypeHit(string x) { targetTypeHit = x; }

	void GetCoordinateObject(LPGAMEOBJECT obj);			// L?y to? ?? c?a object ?? l?u vào sparkC
};

