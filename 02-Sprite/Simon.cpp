#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"
#include "Ground.h"
#include "GetHiddenMoneyObject.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "FishMan.h"
#include "VampireBat.h"
#include "Door.h"
#include "ChangeSceneBlock.h"
#include "Boss.h"


Simon::Simon() : GameObject() {

	LoadResourceFile* loadResourceFile = LoadResourceFile::GetInstance();

	vector<string> animationsSimon = loadResourceFile->GetAnimations("resources\\simon\\simon_ani.xml");
	for each (string animation in animationsSimon)
	{
		AddAnimation(animation);
	}

	weapon = new Weapon();
	nameWeapon = AXE_SUB;

	score = 0;
	item = "";
	energy = 55;
	life = 3;
	HP = 16;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	GameObject::Update(dt);

	if (isStandOnStair == false && isAutoWalk == false)
	{
		if (vy < -0.2f || vy > 0.2f)
			vy += SIMON_GRAVITY * dt;
		else vy += SIMON_GRAVITY_LOWER * dt;

	}

	// Auto walk conditions
	if (isAutoWalk == true)
		DoAutoWalk();

	// Reset untouchable timer if untouchable time has passed
	if (untouchableTimer->IsTimeUp() == true)
		untouchableTimer->Stop();

	// Reset invisibility timer if invisibility time has passed
	if (invisibilityTimer->IsTimeUp() == true)
		invisibilityTimer->Stop();

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occurred, proceed normally
	if (coEvents.size() == 0 && isAutoWalk == false)
	{
		x += dx;
		y += dy;

		if (vy > SIMON_SPEED_Y_LOWER_ZONE)
			isFalling = true;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		if (isAutoWalk == false)
		{
			x += min_tx * dx + nx * 0.1f;
			y += min_ty * dy + ny * 0.1f;
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj))
			{
				if (e->ny != 0)
				{
					// BUG: 
					// Simon deflect ngay l?p t?c va ch?m v?i ground (?ôi lúc) -> không b?t nh?y ???c.
					if (e->ny == CDIR_BOTTOM && (state != DEFLECT || (state == DEFLECT && vy > 0)))
					{
						isCollisionWithStair = false;
						vy = 0;
						isTouchGround = true;
						isFalling = false;

						if (HP == 0)
						{
							SetState(DEAD);
							return;
						}
					}
					else
						y += dy;
				}

				// Khi ?ang lên/xu?ng c?u thang, va ch?m theo tr?c x s? không ???c xét t?i
				if (state == STAIR_UP || state == STAIR_DOWN)
					if (nx != 0) x -= nx * 0.1f;
			}
			else if (dynamic_cast<Candle*>(e->obj) || dynamic_cast<Items*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
			else if (dynamic_cast<GetHiddenMoneyObject*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;

				if (this->AABBx(e->obj) == true)
				{
					e->obj->SetState(TOUCHED);
				}
			}

			else if (dynamic_cast<Water*>(e->obj))
			{
				Water* water = dynamic_cast<Water*>(e->obj);
				water->AddBubbles(x, y + SIMON_BBOX_HEIGHT);

				SetState(DEAD);
				isFallingWater = true;
				return;
			}

			else if (dynamic_cast<FireBall*>(e->obj))
			{
				LoseHP(1);
				e->obj->SetEnable(false);
			}

			else if (e->obj->GetState() == DESTROYED) x += dx;

			else if (e->obj->GetState() == BREAK)
			{
				x += dx;
				y += dy;
			}

			else if (dynamic_cast<Zombie*>(e->obj) || dynamic_cast<BlackLeopard*>(e->obj) || dynamic_cast<FishMan*>(e->obj) || dynamic_cast<VampireBat*>(e->obj) || dynamic_cast<Boss*>(e->obj))
			{
				if (state != POWER && untouchableTimer->IsTimeUp() == true && invisibilityTimer->IsTimeUp() == true)
				{
					untouchableTimer->Start();

					if (dynamic_cast<Zombie*>(e->obj))
					{
						Zombie* zombie = dynamic_cast<Zombie*>(e->obj);
						LoseHP(zombie->GetAttack());
					}
					else if (dynamic_cast<BlackLeopard*>(e->obj))
					{
						BlackLeopard* leopard = dynamic_cast<BlackLeopard*>(e->obj);
						LoseHP(leopard->GetAttack());
					}
					else if (dynamic_cast<FishMan*>(e->obj))
					{
						FishMan* fishman = dynamic_cast<FishMan*>(e->obj);
						LoseHP(fishman->GetAttack());
					}
					else if (dynamic_cast<VampireBat*>(e->obj))
					{
						VampireBat* bat = dynamic_cast<VampireBat*>(e->obj);
						bat->SetState(VAMPIRE_BAT_DESTROYED);	// n?u d?i tông trúng simon thì cho hu?
						LoseHP(bat->GetAttack());
					}
					else if (dynamic_cast<Boss*>(e->obj))
					{
						Boss* boss = dynamic_cast<Boss*>(e->obj);
						LoseHP(boss->GetAttack());
					}
					if (isStandOnStair == false || HP == 0)  // Simon ??ng trên c?u thang s? không b? b?t ng??c l?i
					{
						// ??t tr?ng thái deflect cho simon
						if (e->nx != 0)
						{
							if (e->nx == CDIR_LEFT && this->nx == 1) this->nx = DIR_LEFT;
							else if (e->nx == CDIR_RIGHT && this->nx == -1) this->nx = DIR_RIGHT;
						}

						SetState(DEFLECT);
					}
				}
				else
				{
					if (e->nx != 0)	x + dx;
					if (e->ny != 0) y += dy;
				}
			}
			else if (dynamic_cast<Door*>(e->obj))
			{
				auto door = dynamic_cast<Door*>(e->obj);

				if (door->GetState() == DOOR_2_IDLE)
				{
					vx = 0;

					if (e->nx == CDIR_LEFT)	 // Simon ?ã ?i qua c?a
						x += 1.0f;		 // +1 ?? không b? overlap
					else
					{
						door->SetState(DOOR_2_OPEN);
						door->animations[DOOR_2_OPEN]->SetAniStartTime(GetTickCount());

						isWalkThroughDoor = true;
					}
				}
				else if (e->obj->GetState() == DOOR_1)	// ?i qua c?a c?a scene 1
				{
					SetState(WALK);
					vx = SIMON_WALKING_SPEED_LOWER;
					vy = 0;
					AutoWalk(80, IDLE, DIR_RIGHT);
				}
			}
			else if (dynamic_cast<ChangeSceneBlock*>(e->obj))
			{
				x += dx;
				y += dy;

				ChangeSceneBlock* obj = dynamic_cast<ChangeSceneBlock*>(e->obj);

				if ((obj->GetIDNextScene() == SCENE_3 && this->state == STAIR_DOWN) ||
					(obj->GetIDNextScene() == SCENE_2 && (this->state == STAIR_UP || this->state == WALK)))
				{
					isAutoWalk = false;
					this->changeScene = obj->GetIDNextScene();
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (state == STAND_ATTACK || state == SIT_ATTACK || state == STAIR_UP_ATTACK || state == STAIR_DOWN_ATTACK)
	{
		weapon->SetN(nx);
		weapon->SetWeaponPosition(D3DXVECTOR3(x, y, 0), sitting);
	}

	if (!isHitSubWeapons) weapon->Update(dt, coObjects);

}

void Simon::Render()
{
	if (isFallingWater == true)
		return;

	string tempState = state;
	int alpha = 255;

	// Khi Simon r?i t? trên cao xu?ng thì luôn co chân
	// S? d?ng bi?n t?m ?? không thay ??i tr?ng thái g?c c?a Simon
	if (state != DEAD && IsHit() == false && isFalling == true)
		tempState = JUMP;

	if (untouchableTimer->IsTimeUp() == false)  // ?? render Simon nh?p nháy trong tr?ng thái isUntouchable
		alpha = rand() % 255;
	else if (invisibilityTimer->IsTimeUp() == false)
	{
		float ratio = (float)(GetTickCount() - invisibilityTimer->GetStartTime()) / SIMON_INVISIBILITY_TIME;

		if (ratio < 0.5f)			// nh?p nháy
			alpha = 50;
		else
			alpha = (int)(255 * ratio);	// render rõ d?n theo th?i gian
	}

	animations[tempState]->Render(nx, x, y, alpha);

	if ((tempState == STAND_ATTACK || tempState == SIT_ATTACK || tempState == STAIR_UP_ATTACK || tempState == STAIR_DOWN_ATTACK) && (isHitSubWeapons == false))
	{
		weapon->Render();
	}

	standAttacking = !animations[tempState]->IsCompleted();
	sitAttacking = !animations[tempState]->IsCompleted();
	throwing = !animations[tempState]->IsCompleted();
	powering = !animations[tempState]->IsCompleted();
	stairUpping = !animations[tempState]->IsCompleted();
	deflecting = !animations[tempState]->IsCompleted();
}

void Simon::SetState(string state)
{
	GameObject::SetState(state);

	if (state == IDLE)
	{
		isFallingWater = false;
		sitting = false;
		isStandOnStair = false;
		canMoveDownStair = false;
		canMoveUpStair = false;
		vx = 0;
	}

	else if (state == WALK)
	{
		sitting = false;
		isStandOnStair = false;
		if (nx > 0) vx = SIMON_WALKING_SPEED;
		else vx = -SIMON_WALKING_SPEED;
	}

	else if (state == JUMP)
	{
		isTouchGround = false;
		sitting = false;
		isStandOnStair = false;
		isCollisionWithStair = false;
		vy = -SIMON_JUMP_SPEED_Y;
	}

	else if (state == STAND_ATTACK)
	{
		sitting = false;
		isStandOnStair = false;
		animations[state]->Reset();
		weapon->animations[weapon->GetState()]->Reset();
	}

	else if (state == SIT_ATTACK)
	{
		sitting = true;
		isStandOnStair = false;
		animations[state]->Reset();
		weapon->animations[weapon->GetState()]->Reset();
	}

	else if (state == SIT)
	{
		sitting = true;
		isStandOnStair = false;
		vx = 0;
		vy = 0;
	}

	else if (state == POWER)
	{
		isStandOnStair = false;
		vx = 0;
	}

	else if (state == STAIR_UP)
	{
		isTouchGround = false;
		isStandOnStair = true;
		if (nx > 0) vx = SIMON_STAIR_SPEED_X;
		else vx = -SIMON_STAIR_SPEED_X;
		vy = -SIMON_STAIR_SPEED_Y;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
	}

	else if (state == STAIR_DOWN)
	{
		if (nx > 0) vx = SIMON_STAIR_SPEED_X;
		else vx = -SIMON_STAIR_SPEED_X;
		vy = SIMON_STAIR_SPEED_Y;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
	}

	else if (state == DEFLECT)
	{
		vy = -SIMON_DEFLECT_SPEED_Y;
		if (nx > 0) vx = -SIMON_DEFLECT_SPEED_X;
		else vx = SIMON_DEFLECT_SPEED_X;
	}

	else if (state == STAIR_UP_ATTACK || state == STAIR_DOWN_ATTACK)
	{
		weapon->animations[weapon->GetState()]->Reset();
		sitting = false;
		vx = 0;
		vy = 0;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
	}

	else if (state == DEAD)
	{
		untouchableTimer->Stop();
		invisibilityTimer->Stop();
		vx = 0;
		vy = 0;
	}

}

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	// sprite có kích th??c là 60x66, bbox là 40x62
	left = x + 15; //30,60
	top = y + 2;  //62,66
	right = left + SIMON_BBOX_WIDTH;
	bottom = top + SIMON_BBOX_HEIGHT;

}

void Simon::LoseHP(int x)
{
	HP -= x;

	if (HP <= 0)
		HP = 0;
}

void Simon::GetBoundingBoxFoot(float& left, float& top, float& right, float& bottom)
{
	top += 55;
	bottom += 10;  // bottom +5 ?? xét cho va ch?m v?i b?c thang ??u tiên khi b??c xu?ng
	left += 5;
	right -= 5;
}

#pragma region CheckState

bool Simon::IsJumping()
{
	return (state == JUMP && jumping);
}

bool Simon::IsStandAttacking()
{
	return (state == STAND_ATTACK && standAttacking);
}

bool Simon::IsSitAttacking()
{
	return (state == SIT_ATTACK && sitAttacking);
}

bool Simon::IsThrowing()
{
	return (state == THROW && throwing);
}

bool Simon::IsPowering()
{
	return (state == POWER && powering);
}

bool Simon::IsDeflecting()
{
	return (state == DEFLECT && deflecting);
}

bool Simon::IsStairUpping()
{
	return (state == STAIR_UP && stairUpping);
}

#pragma endregion CheckState
void Simon::CheckCollisionWithStair(vector<LPGAMEOBJECT>* listStair)
{
	float simonLeft, simonTop, simonRight, simonBottom;
	GetBoundingBox(simonLeft, simonTop, simonRight, simonBottom);

	GetBoundingBoxFoot(simonLeft, simonTop, simonRight, simonBottom);
	for (UINT i = 0; i < listStair->size(); i++)
	{
		if (listStair->at(i)->GetType() == "BOTTOM")
		{
			float stair_l, stair_t, stair_r, stair_b;
			listStair->at(i)->GetBoundingBox(stair_l, stair_t, stair_r, stair_b);
			if (Game::AABB(simonLeft, simonTop, simonRight, simonBottom, stair_l, stair_t, stair_r, stair_b))
			{
				if (listStair->at(i)->GetState() == STAIR_LEFT_UP) stairDirection = 1;
				else stairDirection = -1;

				stairCollided = listStair->at(i);
				isCollisionWithStair = true;
				canMoveUpStair = true;
				if (simonBottom > stair_b)
				{
					canMoveDownStair = false;
				}
				else if (simonTop - 10 < stair_t) // -10 have it to moving down first stair
				{
					canMoveDownStair = true;
				}
				break;
			}
		}
		else if (listStair->at(i)->GetType() == "TOP")
		{
			float stair_l, stair_t, stair_r, stair_b;
			listStair->at(i)->GetBoundingBox(stair_l, stair_t, stair_r, stair_b);

			if (Game::AABB(simonLeft, simonTop, simonRight, simonBottom, stair_l, stair_t, stair_r, stair_b))
			{
				if (listStair->at(i)->GetState() == STAIR_LEFT_UP) stairDirection = 1;
				else stairDirection = -1;

				stairCollided = listStair->at(i);
				isCollisionWithStair = true;
				canMoveDownStair = true;
				canMoveUpStair = false;
				if (simonBottom > stair_b)
				{
					canMoveUpStair = true;
				}
				break;
			}
		}
	}
}

bool Simon::CheckCollisionWithItem(vector<LPGAMEOBJECT>* listItem)
{
	for (UINT i = 0; i < listItem->size(); i++)
	{
		if (listItem->at(i)->IsEnable() == false)
			continue;

		if (this->AABBx(listItem->at(i)))
		{
			listItem->at(i)->isEnable = false;

			string nameItem = listItem->at(i)->GetState();

			if (nameItem == DAGGER ||
				nameItem == AXE ||
				nameItem == HOLY_WATER ||
				nameItem == BOOMERANG ||
				nameItem == STOP_WATCH)
			{
				nameWeapon = ItemToSubWeapon(nameItem);
			}

			else if (nameItem == SMALL_HEART)
			{
				energy += 1;
			}

			else if (nameItem == LARGE_HEART)
			{
				energy += 5;
			}

			else if (nameItem == CROSS)
			{
				isGotCrossItem = true;
			}

			else if (nameItem == INVISIBILITY_POTION)
			{
				invisibilityTimer->Start();
			}

			else if (nameItem == CHAIN)
			{
				SetState(POWER); // ??i tr?ng thái power - bi?n hình nh?p nháy các ki?u ?à ?i?u
				vx = 0;
				// lên ??i whip
				if (weapon->GetState() == MAGIC_WHIP) weapon->SetState(SHORT_CHAIN);
				else if (weapon->GetState() == SHORT_CHAIN) weapon->SetState(LONG_CHAIN);
			}

			else if (nameItem == MONEY_BAG_RED)
			{
				score += 100;
			}
			else if (nameItem == MONEY_BAG_BLUE)
			{
				score += 400;
			}
			else if (nameItem == MONEY_BAG_WHITE)
			{
				score += 700;
			}
			else if (nameItem == MONEY_BAG_FLASHING)
			{
				score += 1000;
			}

			else if (nameItem == DOUBLE_SHOT)
			{
				item = nameItem;
				isGotDoubleShotItem = true;
			}

			else if (nameItem == TRIPLE_SHOT)
			{
				item = nameItem;
				isGotTripleShotItem = true;
			}

			else if (nameItem == PORK_CHOP)
			{
				HP += 2;
				if (HP > SIMON_HP)
					HP = SIMON_HP;
			}
			else if (nameItem == MAGIC_CRYSTAL)
			{
				HP += SIMON_HP;
			}

			return true;
		}
	}
}

void Simon::CheckCollisionWithEnemyActiveArea(vector<LPGAMEOBJECT>* listObjects)
{
	float simon_l, simon_t, simon_r, simon_b;

	GetBoundingBox(simon_l, simon_t, simon_r, simon_b);

	for (UINT i = 0; i < listObjects->size(); i++)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(listObjects->at(i));

		if (enemy == NULL)
			continue;

		// Không c?n xét vùng active n?a khi nó ?ang active / destroyed
		if (enemy->GetState() == ZOMBIE_ACTIVE ||
			enemy->GetState() == FISHMAN_ACTIVE ||
			enemy->GetState() == BLACK_LEOPARD_ACTIVE ||
			enemy->GetState() == VAMPIRE_BAT_ACTIVE ||
			enemy->GetState() == BOSS_ACTIVE ||
			enemy->GetState() == DESTROYED)
			continue;

		float enemy_l, enemy_t, enemy_r, enemy_b;
		enemy->GetActiveBoundingBox(enemy_l, enemy_t, enemy_r, enemy_b);

		if (Game::AABB(simon_l, simon_t, simon_r, simon_b, enemy_l, enemy_t, enemy_r, enemy_b) == true)
		{
			D3DXVECTOR2 enemyEntryPostion = enemy->GetEntryPosition();

			if (dynamic_cast<Zombie*>(enemy))
			{
				Zombie* zombie = dynamic_cast<Zombie*>(enemy);

				if (zombie->GetState() == ZOMBIE_INACTIVE && zombie->IsAbleToActivate() == true)
					zombie->SetState(ZOMBIE_ACTIVE);
			}
			else if (dynamic_cast<BlackLeopard*>(enemy))
			{
				BlackLeopard* leopard = dynamic_cast<BlackLeopard*>(enemy);
				if (leopard->GetState() == BLACK_LEOPARD_IDLE)
					leopard->SetState(BLACK_LEOPARD_ACTIVE);
			}
			else if (dynamic_cast<FishMan*>(enemy))
			{
				FishMan* fishman = dynamic_cast<FishMan*>(enemy);

				if (fishman->GetState() == FISHMAN_INACTIVE && fishman->IsAbleToActivate() == true)
					fishman->SetState(FISHMAN_ACTIVE);
			}
			else if (dynamic_cast<VampireBat*>(enemy))
			{
				VampireBat* bat = dynamic_cast<VampireBat*>(enemy);

				if (bat->GetState() == VAMPIRE_BAT_INACTIVE && bat->IsAbleToActivate() == true)
					bat->SetState(VAMPIRE_BAT_ACTIVE);
			}
			else if (dynamic_cast<Boss*>(enemy))
			{
				Boss* boss = dynamic_cast<Boss*>(enemy);
				boss->SetState(BOSS_ACTIVE);
			}
		}
	}
}

void Simon::DoAutoWalk()
{
	if (abs(dx) <= abs(autoWalkDistance))
	{
		x += dx;
		y += dy;
		autoWalkDistance -= dx;
	}
	else
	{
		x += autoWalkDistance;
		state = stateAfterAutoWalk;
		nx = nxAfterAutoWalk;

		SetState(state);
		if (state == STAIR_DOWN) y += 1.0f; // + 1.0f ?? ??m b?o simon s? va ch?m v?i b?c thang trong l?n update k? ti?p

		isAutoWalk = false;
		autoWalkDistance = 0;
		stateAfterAutoWalk = -1;
		nxAfterAutoWalk = 0;
	}
}

void Simon::AutoWalk(float distance, string new_state, int new_nx)
{
	isAutoWalk = true;

	autoWalkDistance = distance;
	stateAfterAutoWalk = new_state;
	nxAfterAutoWalk = new_nx;
}

bool Simon::IsHit()
{
	return state == STAND_ATTACK || state == SIT_ATTACK || state == STAIR_DOWN_ATTACK || state == STAIR_UP_ATTACK;
}
