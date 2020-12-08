#pragma once
#include <algorithm>

#include "GameObject.h"
#include "Weapon.h"
#include "LoadResource.h"
#include "Const.h"
#include "Timer.h"
#include "Items.h"
#include "Candle.h"
#include "FireBall.h"
#include "BlackLeopard.h"
#include "Water.h"
#include "debug.h"
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
#include "BreakWall.h"

class Simon : public GameObject
{
	Weapon* weapon;

	string nameWeapon;
	int score;
	string item;
	int energy;
	int life;
	int HP;

	// auto-walk
	float autoWalkDistance = 0;
	string stateAfterAutoWalk = "";
	int nxAfterAutoWalk = 0;

public:

	Timer* untouchableTimer = new Timer(SIMON_UNTOUCHABLE_TIME);
	Timer* invisibilityTimer = new Timer(SIMON_INVISIBILITY_TIME);

	bool jumping = false;
	bool sitting = false;
	bool standAttacking = false;
	bool sitAttacking = false;
	bool throwing = false;
	bool powering = false;
	bool stairUpping = false;
	bool deflecting = false;

	bool isDead = false;
	bool isTouchGround = false;
	bool isFalling = false;
	bool isFallingWater = false;
	bool isStandOnStair = false;	// tr?ng thái ?ang ??ng trên c?u thang 
	bool canMoveUpStair = false;	// có th? di chuy?n lên c?u thang
	bool canMoveDownStair = false;	// có th? di chuy?n xu?ng c?u thang
	bool isAutoWalk = false;		// t? ??ng ?i
	bool isWalkThroughDoor = false;	// ?i qua c?a
	bool isHitSubWeapons = false;	// xác ??nh xem là hit b?ng roi hay subweapon
	bool isGotChainItem = false;	// xác ??nh xem có nh?t ???c Chain item hay không, dùng ?? update whip
	bool isGotDoubleShotItem = false; // Double shot item
	bool isGotTripleShotItem = false; // Triple shot item
	bool isGotCrossItem = false;
	bool isCollisionWithStair = false;

	int changeScene = -1;			// l?u id Scene k? ti?p khi Simon va ch?m v?i ChangeSceneObject

	int stairDirection = 0;			// 1: trái d??i - ph?i trên, -1: trái trên - ph?i d??i

	LPGAMEOBJECT stairCollided = nullptr; // l?u b?c thang va ch?m v?i simon -> ?? xét v? trí cho chu?n trong hàm PositionCorrection

	///
	Simon();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetState(string state);

	virtual void GetBoundingBoxFoot(float& left, float& top, float& right, float& bottom);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	bool IsJumping();
	bool IsSitting() { return sitting; }
	bool IsStandAttacking();
	bool IsSitAttacking();
	bool IsThrowing();
	bool IsPowering();
	bool IsDeflecting();
	bool IsStairUpping();

	// Get function
	int GetEnergy() { return this->energy; }
	int GetLife() { return this->life; }
	int GetScore() { return this->score; }
	int GetHP() { return this->HP; }
	string GetItem() { return this->item; }
	Weapon* GetWeapon() { return this->weapon; }
	string GetSubWeapon() { return this->nameWeapon; }
	string ItemToSubWeapon(string itemName) { return itemName + "_SUB"; }

	// Properties change
	void AddScore(int x) { score += x; }
	void LoseEnergy(int x) { energy -= x; }
	void LoseHP(int x);
	void SetHP(int x) { HP = x; }
	void SetEnergy(int x) { energy = x; }
	void SetSubWeapon(string x) { nameWeapon = x; }

	// Ki?m tra va ch?m v?i danh sách b?c thang
	void CheckCollisionWithStair(vector<LPGAMEOBJECT>* listStair);

	// Ki?m tra va ch?m v?i danh sách item
	bool CheckCollisionWithItem(vector<LPGAMEOBJECT>* listItem);

	// Ki?m tra va ch?m v?i vùng ho?t ??ng c?a enemy
	void CheckCollisionWithEnemyActiveArea(vector<LPGAMEOBJECT>* listObjects);

	// Gi? cho Simon ??ng yên trên b?c thang
	void StandOnStair() { vx = vy = 0; }

	// Auto-walk
	void AutoWalk(float distance, string new_state, int new_nx);
	void DoAutoWalk();

	// Xác ??nh tr?ng thái ?ang ?ánh
	bool IsHit();
};