#include "GUI.h"

GUI::GUI()
{
	SetRect(&rect, 0, 8, SCREEN_WIDTH, SCREEN_HEIGHT);
	information = "SCORE-000000 TIME 0000 SCENE 00\n";
	information += "PLAYER                   -00\n";
	information += "ENEMY                   P-00\n";
}

GUI::~GUI()
{
}

void GUI::Update(DWORD time, int idScene, Simon* simon, Boss* boss)
{
	heart = simon->GetEnergy() < 10 ? "0" + std::to_string(simon->GetEnergy()) : std::to_string(simon->GetEnergy());
	life = simon->GetLife() < 10 ? "0" + std::to_string(simon->GetLife()) : std::to_string(simon->GetLife());
	simonHp = simon->GetHP();
	bossHp = boss->GetHP();

	unsigned int score = simon->GetScore();
	string scoreTempt;
	if (score < 10)
	{
		scoreTempt = "00000" + std::to_string(score);
	}
	else if (score < 100)
	{
		scoreTempt = "0000" + std::to_string(score);
	}
	else if (score < 1000)
	{
		scoreTempt = "000" + std::to_string(score);
	}
	else if (score < 10000)
	{
		scoreTempt = "00" + std::to_string(score);
	}
	else if (score < 100000)
	{
		scoreTempt = "0" + std::to_string(score);
	}
	else
	{
		scoreTempt = std::to_string(score);
	}

	information = "SCORE-" + scoreTempt + " TIME 0" + std::to_string(time) + " SCENE 0" + std::to_string(idScene) + "\n";
	information = information + "PLAYER                 -" + heart + "\n";
	information += "ENEMY                 P-" + life + "\n";
}

void GUI::Render(Simon* simon)
{
	Game::GetInstance()->DrawUIText(this->information, rect);
	Sprites::GetInstance()->Get("black_board")->DrawHud(260, 26);
	Sprites::GetInstance()->Get("heart_hud")->DrawHud(351, 26);

	if (simon->GetSubWeapon() == "DAGGER_SUB") {
		Sprites::GetInstance()->Get("Dagger")->DrawHud(276, 35);
	}
	else if (simon->GetSubWeapon() == "AXE_SUB") {
		Sprites::GetInstance()->Get("Axe_1")->DrawHud(276, 33);
	}
	else if (simon->GetSubWeapon() == "BOOMERANG_SUB") {
		Sprites::GetInstance()->Get("Boomerang_1")->DrawHud(276, 33);
	}
	else if (simon->GetSubWeapon() == "HOLYWATER_SUB") {
		Sprites::GetInstance()->Get("item_holywater")->DrawHud(276, 31);
	}
	else if (simon->GetSubWeapon() == "STOP_WATCH_SUB") {
		Sprites::GetInstance()->Get("item_stopwatch")->DrawHud(276, 29);
	}

	if (simon->isGotDoubleShotItem) {
		Sprites::GetInstance()->Get("item_doubleshot")->DrawHud(420, 27);
	}
	else if (simon->isGotTripleShotItem) {
		Sprites::GetInstance()->Get("item_tripleshot")->DrawHud(420, 27);
	}

	for (int i = 0; i < 16; i++)
		if (i < simonHp)
			Sprites::GetInstance()->Get("simon_hp")->DrawHud(109 + i * 9, 26, 255);
		else
			Sprites::GetInstance()->Get("sub_hp")->DrawHud(109 + i * 9, 26, 255);

	for (int i = 0; i < 16; i++)
		if (i < bossHp)
			Sprites::GetInstance()->Get("boss_hp")->DrawHud(109 + i * 9, 42, 255);
		else
			Sprites::GetInstance()->Get("sub_hp")->DrawHud(109 + i * 9, 42, 255);
}
