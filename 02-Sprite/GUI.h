#pragma once
#include "d3dx9.h"
#include <string>
#include "Simon.h"

class GUI
{
	RECT rect;
	string information;

	int simonHp;
	int bossHp;
	int score;
	string heart;
	string life;
	int time;
	int subWeapon;
public:
	GUI();
	~GUI();

	virtual void Update(DWORD time, int idScene, Simon* simon);
	void Render(Simon* simon);

	void SetBossHp(int hp) { this->bossHp = hp; }
};

