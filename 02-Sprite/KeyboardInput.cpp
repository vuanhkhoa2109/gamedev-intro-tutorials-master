#include "KeyboardInput.h"

KeyBoardInput::KeyBoardInput(Game* game, SceneManager* scene)
{
	this->game = game;
	this->scene = scene;
}

KeyBoardInput::~KeyBoardInput()
{
}

void KeyBoardInput::KeyState(BYTE* state)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", state);
	Simon* simon = scene->GetSimon();

	if (simon->GetState() == DEAD)
		return;

	if (simon->isAutoWalk == true)
		return;

	// n?u simon ?ang nh?y và ch?a ch?m ??t, ti?p t?c render tr?ng thái nh?y
	if ((simon->GetState() == JUMP || simon->GetState() == IDLE)
		&& simon->isTouchGround == false)
		return;

	if (isNeedToWaitingAnimation == true)
	{
		/*	if (scene->GetSimon()->IsJumping())
				return;*/

		if (scene->GetSimon()->IsStandAttacking())
			return;

		if (scene->GetSimon()->IsSitAttacking())
			return;

		if (scene->GetSimon()->IsThrowing())
			return;

		if (scene->GetSimon()->IsPowering())
			return;

		if (scene->GetSimon()->IsDeflecting())
			return;

		if (scene->GetSimon()->isAutoWalk == true)
			return;

		if (scene->GetSimon()->GetState() == STAIR_UP && scene->GetSimon()->animations[STAIR_UP]->IsOver(200) == false)
			return;

		if (scene->GetSimon()->GetState() == STAIR_DOWN && scene->GetSimon()->animations[STAIR_DOWN]->IsOver(200) == false)
			return;

		if (simon->GetState() == STAIR_UP_ATTACK && simon->animations[STAIR_UP_ATTACK]->IsOver(300) == false)
			return;

		if (simon->GetState() == STAIR_DOWN_ATTACK && simon->animations[STAIR_DOWN_ATTACK]->IsOver(300) == false)
			return;

	}
	else
	{
		// ??t l?i bi?n ch? render animation
		isNeedToWaitingAnimation = true;

		// ?? tránh vi?c ? frame ti?p theo r?i vào tr?ng thái ch? render animation 
		// (vì animation == 200ms, m?t frame == 30ms nên s? ph?i b? ch? dù cho có bi?n isNeedToWaitingAnimation),
		// do ?ó c?n reset l?i animation start time v? 0
		simon->animations[simon->GetState()]->SetAniStartTime(0);
	}


	// Xét tr?ng thái phím
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (StairCollisionsDetection() == true && simon->isStandOnStair == true)
		{
			if (simon->stairDirection == 1) // c?u thang trái d??i - ph?i trên
			{
				Simon_Stair_Up();
			}
			else {
				Simon_Stair_Down();
			}

			return;
		}

		Simon_Walk_Right();
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (StairCollisionsDetection() == true && simon->isStandOnStair == true)
		{
			if (simon->stairDirection == 1) // c?u thang trái d??i - ph?i trên
			{
				Simon_Stair_Down();
			}
			else {
				Simon_Stair_Up();
			}

			return;
		}

		Simon_Walk_Left();
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (StairCollisionsDetection() == true)
		{
			Simon_Stair_Down();
			return;
		}

		if (simon->isTouchGround == false || simon->isFalling == true)
		{
			simon->SetState(IDLE);
			return;
		}

		simon->SetState(SIT);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		if (StairCollisionsDetection() == true)
		{
			Simon_Stair_Up();
			return;
		}

		simon->SetState(IDLE);
	}
	else
	{
		simon->isHitSubWeapons = false;
		if (StairCollisionsDetection() == true)
		{
			if (Simon_Stair_Stand() == true)
			{
				return;
			}
		}

		simon->SetState(IDLE);
	}
}

void KeyBoardInput::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	if (scene->GetSimon()->GetState() == DEAD)
		return;

	switch (KeyCode)
	{
	case DIK_SPACE:
		Simon_Jump();
		break;
	case DIK_D:
		if (game->IsKeyDown(DIK_UP))
			Simon_Hit_SubWeapon();
		else
			Simon_Hit();
		break;
	case DIK_X:
		Simon_Hit_SubWeapon();
		break;
	case DIK_0:
		scene->GetSimon()->SetSubWeapon(DAGGER_SUB);
		break;
	case DIK_1:
		scene->GetSimon()->SetSubWeapon(AXE_SUB);
		break;
	case DIK_2:
		scene->GetSimon()->SetSubWeapon(BOOMERANG_SUB);
		break;
	case DIK_3:
		scene->GetSimon()->SetSubWeapon(HOLY_WATER_SUB);
		break;
	case DIK_4:
		scene->GetSimon()->SetSubWeapon(STOP_WATCH_SUB);
		break;
	case DIK_5:
		scene->GetSimon()->isGotCrossItem = true;
		break;
	case DIK_6:
		scene->GetSimon()->isGotDoubleShotItem = true;
		break;
	case DIK_7:
		scene->GetSimon()->isGotTripleShotItem = true;
		break;
	case DIK_8:
		scene->GetSimon()->invisibilityTimer->Start();
		break;
	case DIK_Q:
		scene->Init(SCENE_1);
		scene->SetGameState(GAMESTATE_1);
		break;
	case DIK_W:
		scene->Init(SCENE_2);
		scene->SetGameState(GAMESTATE_2_1);
		break;
	case DIK_E:
		scene->Init(SCENE_2);
		scene->SetGameState(GAMESTATE_2_2);
		break;
	case DIK_R:
		scene->Init(SCENE_2);
		scene->SetGameState(GAMESTATE_2_3);
		break;
	case DIK_T:
		scene->Init(SCENE_3);
		scene->SetGameState(GAMESTATE_3_1);
		break;
	case DIK_Y:
		scene->Init(SCENE_3);
		scene->SetGameState(GAMESTATE_3_2);
		break;
	default:
		break;
	}
}

void KeyBoardInput::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void KeyBoardInput::Simon_Walk_Left()
{
	scene->GetSimon()->SetN(-1);
	scene->GetSimon()->SetState(WALK);
}

void KeyBoardInput::Simon_Walk_Right()
{
	scene->GetSimon()->SetN(1);
	scene->GetSimon()->SetState(WALK);
}

void KeyBoardInput::Simon_Jump()
{
	if (scene->GetSimon()->isTouchGround == false || scene->GetSimon()->GetState() == JUMP ||
		scene->GetSimon()->GetState() == STAND_ATTACK ||
		scene->GetSimon()->GetState() == SIT_ATTACK)
		return;

	scene->GetSimon()->SetState(JUMP);
}

void KeyBoardInput::Simon_Hit()
{
	if ((scene->GetSimon()->GetState() == STAND_ATTACK || scene->GetSimon()->GetState() == SIT_ATTACK))
		return;
	if (scene->GetSimon()->GetState() == IDLE || scene->GetSimon()->GetState() == JUMP || scene->GetSimon()->GetState() == WALK)
	{
		scene->GetSimon()->SetState(STAND_ATTACK);
		if (scene->GetSimon()->isTouchGround == true)
		{
			scene->GetSimon()->vx = 0;
		}
	}
	else if (scene->GetSimon()->GetState() == SIT)
	{
		scene->GetSimon()->SetState(SIT_ATTACK);
	}
	else if (scene->GetSimon()->GetState() == STAIR_UP)
	{
		scene->GetSimon()->SetState(STAIR_UP_ATTACK);
	}
	else if (scene->GetSimon()->GetState() == STAIR_DOWN)
	{
		scene->GetSimon()->SetState(STAIR_DOWN_ATTACK);
	}
}

void KeyBoardInput::Simon_Hit_SubWeapon()
{
	Simon* simon = scene->GetSimon();
	//SubWeapon* subweapon = scene->GetSubWeapon();

	vector<SubWeapon*>* subweaponList = scene->GetWeaponList();
	SubWeapon* subweapon;

	if (simon->GetSubWeapon() == "") // không có v? khí 
		return;

	if (simon->GetSubWeapon() == STOP_WATCH_SUB)
	{
		/*	if (simon->GetEnergy() < 5)
				return;*/
		if (scene->stopWatchTimer->IsTimeUp() == false) // ?ang s? d?ng stop watch
			return;

		subweaponList->at(0)->SetEnable(false);
	}

	if (subweaponList->at(0)->IsEnable() == false)
		subweapon = subweaponList->at(0);

	else if (subweaponList->at(1)->IsEnable() == false && (scene->doubleShotTimer->IsTimeUp() == false || scene->tripleShotTimer->IsTimeUp() == false))
		subweapon = subweaponList->at(1);
	else if (subweaponList->at(2)->IsEnable() == false && scene->tripleShotTimer->IsTimeUp() == false)
		subweapon = subweaponList->at(2);
	else return;

	if (simon->GetState() == IDLE || simon->GetState() == JUMP ||
		simon->GetState() == SIT || simon->GetState() == STAIR_UP ||
		simon->GetState() == STAIR_DOWN)
	{
		float sx, sy;

		// position
		simon->GetPosition(sx, sy);

		if (simon->GetState() == SIT) sy += 25.0f; // kh?p v? trí tay
		else sy += 10.0f;
		if (simon->GetN() < 0) sx += 30.0f;
		else sx += 30.0f;

		subweapon->SetPosition(sx, sy);

		// orientation
		subweapon->SetN(simon->GetN());

		// state subweapon
		subweapon->SetEnable(true);
		subweapon->SetState(simon->GetSubWeapon());

		if (subweapon->GetState() == STOP_WATCH_SUB)
		{
			simon->LoseEnergy(5);
			scene->stopWatchTimer->Start();
		}
		else
		{
			simon->LoseEnergy(1);
			simon->isHitSubWeapons = true;
			Simon_Hit();
		}
	}
}

void KeyBoardInput::Simon_Stair_Down()
{
	Simon* simon = scene->GetSimon();
	string prevState = simon->GetState();
	int stairDirection = simon->stairDirection;

	if (simon->canMoveDownStair == false)
	{
		simon->SetState(IDLE);

		return;
	}


	// Auto-walk c?a Simon ?i ??n ?úng ??u c?u thang r?i m?i b??c lên
	if (simon->isStandOnStair == false)
	{
		float stair_x, simon_x, temp_y;

		simon->stairCollided->GetPosition(stair_x, temp_y);
		simon->GetPosition(simon_x, temp_y);

		if (stairDirection == -1) stair_x -= 28.0f;

		if (stair_x < simon_x) simon->SetN(-1);
		else if (stair_x > simon_x) simon->SetN(1);
		else return;

		simon->SetState(WALK);
		simon->vy = 0;
		simon->AutoWalk(stair_x - simon_x, STAIR_DOWN, -stairDirection);
		simon->isStandOnStair = true;

		return;
	}
	else
	{
		simon->SetN(-simon->stairDirection);
		simon->SetState(STAIR_DOWN);
	}
	return;
}

void KeyBoardInput::Simon_Stair_Up()
{
	Simon* simon = scene->GetSimon();
	string prevState = simon->GetState();
	int stairDirection = simon->stairDirection;

	if (simon->canMoveUpStair == false)
	{
		if (prevState == STAIR_UP || prevState == STAIR_DOWN)
		{
			int nx = simon->stairDirection;
			simon->SetN(nx);
			simon->SetState(STAIR_UP);
			simon->AutoWalk(16 * nx, IDLE, nx);
		}

		return;
	}

	// Auto-walk c?a Simon ?i ??n ?úng chân c?u thang r?i m?i b??c lên
	if (simon->isStandOnStair == false)
	{
		float stair_x, simon_x, temp_y;

		simon->stairCollided->GetPosition(stair_x, temp_y);
		simon->GetPosition(simon_x, temp_y);

		if (stairDirection == 1) stair_x -= 31.0f;
		else stair_x += 5.0f;

		if (stair_x < simon_x) simon->SetN(-1);
		else if (stair_x > simon_x)  simon->SetN(1);
		else return;

		simon->SetState(WALK);
		simon->vy = 0;
		simon->AutoWalk(stair_x - simon_x, STAIR_UP, stairDirection);
		simon->isStandOnStair = true;

		return;
	}
	else
	{
		simon->SetN(stairDirection);
		simon->SetState(STAIR_UP);
	}

	return;
}

bool KeyBoardInput::Simon_Stair_Stand()
{
	Simon* simon = scene->GetSimon();

	if (simon->GetState() == STAIR_UP || simon->GetState() == STAIR_DOWN ||
		simon->GetState() == STAIR_UP_ATTACK || simon->GetState() == STAIR_DOWN_ATTACK)
	{
		if (simon->GetState() == STAIR_UP_ATTACK)
		{
			simon->SetState(STAIR_UP);
			isNeedToWaitingAnimation = false;
		}
		else if (simon->GetState() == STAIR_DOWN_ATTACK)
		{
			simon->SetState(STAIR_DOWN);
			isNeedToWaitingAnimation = false;
		}

		simon->StandOnStair();
		simon->animations[simon->GetState()]->Reset();

		return true;
	}

	return false;
}

bool KeyBoardInput::StairCollisionsDetection()
{
	Simon* simon = scene->GetSimon();
	vector<LPGAMEOBJECT>* listStairs = scene->GetListStairs();

	simon->CheckCollisionWithStair(listStairs);
	return simon->isCollisionWithStair;
}
