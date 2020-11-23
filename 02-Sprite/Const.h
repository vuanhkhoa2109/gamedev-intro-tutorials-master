#pragma once
#include <string>

#include <Windows.h>
#include <d3dx9.h>

using namespace std;

#pragma region define window

#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480

#define DEFAULT_CELL_WIDTH		256
#define DEFAULT_CELL_HEIGHT		240

#define MAX_FRAME_RATE 200

#pragma endregion

// Time play
#define DEFAULT_TIME_PLAY 300

////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region PathFile

// Font
#define FILEPATH_FONT L"Font\\prstart.ttf"

// Scenes
#define FILEPATH_TEX_MAP_SCENE_1 L"Scenes\\Scene1.png"
#define FILEPATH_DATA_MAP_SCENE_1 L"Scenes\\Scene1_map.txt"
#define FILEPATH_OBJECTS_SCENE_1 L"Scenes\\Scene1_objects.txt"

#define FILEPATH_TEX_MAP_SCENE_2 L"Scenes\\Scene2.png"
#define FILEPATH_DATA_MAP_SCENE_2 L"Scenes\\Scene2_map.txt"
#define FILEPATH_OBJECTS_SCENE_2 L"Scenes\\Scene2_objects.txt"

#define FILEPATH_TEX_MAP_SCENE_3		L"Scenes\\Scene3.png"
#define FILEPATH_DATA_MAP_SCENE_3		L"Scenes\\Scene3_map.txt"
#define FILEPATH_OBJECTS_SCENE_3		L"Scenes\\Scene3_objects.txt"

// Player
#define FILEPATH_TEX_HP L"resources\\HP.png"
#define FILEPATH_TEX_RECT L"resources\\Rect.png"

#pragma endregion

// define id texture
enum TexId
{
	SCENE_1,
	SCENE_2,
	SCENE_3,
	ID_TEX_HP,
	ID_TEX_RECT
};

const int ID_BBOX = 100000;
const int ID_BBOX_2 = 9999;

////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region define State

// Game
#define GAMESTATE_1		0   // SCENE_1
#define GAMESTATE_2_1	1	// SCENE_2 - phòng 1
#define GAMESTATE_2_2	2	// SCENE_2 - phòng 2
#define GAMESTATE_2_2_1	3	// SCENE_2 - phòng 2 - c?u thang xu?ng 1
#define GAMESTATE_2_2_2	4	// SCENE_2 - phòng 2 - c?u thang xu?ng 2
#define GAMESTATE_2_3	5	// SCENE_2 - phòng 3 (Boss)
#define GAMESTATE_3_1	6	// SCENE_3 - c?u thang lên 1
#define GAMESTATE_3_2	7	// SCENE_3 - c?u thang lên 2

// Orientation
#define DIR_LEFT		-1
#define DIR_RIGHT		1

// Collision direction
#define CDIR_LEFT		1.0f
#define CDIR_RIGHT		-1.0f
#define CDIR_TOP		1.0f
#define	CDIR_BOTTOM		-1.0f	

// Simon
const string IDLE = "SIMON_IDLE";
const string WALK = "SIMON_WALKING";
const string JUMP = "SIMON_JUMPING";
const string SIT = "SIMON_SITTING";
const string STAND_ATTACK = "SIMON_STAND_ATTACKING";
const string SIT_ATTACK = "SIMON_SIT_ATTACKING";
const string THROW = "SIMON_THROWING";
const string DIE = "SIMON_DIE";
const string POWER = "SIMON_POWERING";
const string STAIR_UP = "SIMON_STAIR_UP";
const string STAIR_DOWN = "SIMON_STAIR_DOWN";
const string AUTO_WALK = "SIMON_AUTO_WALK";
const string DEFLECT = "SIMON_DEFLECT";
const string STAIR_UP_ATTACK = "SIMON_STAIR_UP_ATTACK";
const string STAIR_DOWN_ATTACK = "SIMON_STAIR_DOWN_ATTACK";
const string DEAD = "SIMON_DEAD";

// Weapon
const string MAGIC_WHIP = "MAGIC_WHIP";
const string SHORT_CHAIN = "SHORT_CHAIN";
const string LONG_CHAIN = "LONG_CHAIN";

// Candle
const string LARGE_CANDLE = "LARGE_CANDLE";
const string CANDLE_DESTROYED = "EFFECT";
const string CANDLE = "CANDLE";

// Ground
const string GROUND_1 = "GROUND_1";
const string GROUND_2 = "GROUND_2";

// Hidden Object
const string TOUCHED = "TOUCHED";
const string NEVER_TOUCH = "NEVER_TOUCH";

// Items
const string STOP_WATCH = "STOP_WATCH";
const string DAGGER = "DAGGER";
const string AXE = "AXE";
const string HOLY_WATER = "HOLY_WATER";
const string BOOMERANG = "BOOMERANG";
const string SMALL_HEART = "SMALL_HEART";
const string LARGE_HEART = "LARGE_HEART";
const string CROSS = "CROSS";
const string INVISIBILITY_POTION = "INVISIBILITY_POTION";
const string CHAIN = "CHAIN";
const string MONEY_BAG_RED = "MONEY_BAG_RED";
const string MONEY_BAG_BLUE = "MONEY_BAG_BLUE";
const string MONEY_BAG_WHITE = "MONEY_BAG_WHITE";
const string MONEY_BAG_FLASHING = "MONEY_BAG_FLASHING";
const string DOUBLE_SHOT = "DOUBLE_SHOT";
const string TRIPLE_SHOT = "TRIPLE_SHOT";
const string PORK_CHOP = "PORK_CHOP";
const string MAGIC_CRYSTAL = "MAGIC_CRYSTAL";

// Sub weapons
const string DAGGER_SUB = "DAGGER_SUB";
const string AXE_SUB = "AXE_SUB";
const string BOOMERANG_SUB = "BOOMERANG_SUB";
const string HOLY_WATER_SUB = "HOLYWATER_SUB";
const string HOLY_WATER_SHATTERED_SUB = "HOLY_WATER_SHATTERED_SUB";
const string STOP_WATCH_SUB = "STOP_WATCH_SUB";

// Stair
const string STAIR_LEFT_UP = "STAIR_LEFT_UP";
const string STAIR_RIGHT_DOWN = "STAIR_RIGHT_DOWN";

// Door
const string  DOOR_1 = "DOOR_1";
const string  DOOR_2_IDLE = "DOOR_2_IDLE";
const string  DOOR_2_OPEN = "DOOR_2_OPEN";

// Enemy (chung cho Zombie, Black Leopard, Bat...)
const string ACTIVE = "ACTIVE";
const string DESTROYED = "EFFECT";
const string INACTIVE = "INACTIVE";

// Zombie 
const string  ZOMBIE_ACTIVE = "ZOMBIE_ACTIVE";
const string  ZOMBIE_DESTROYED = "EFFECT";
const string  ZOMBIE_INACTIVE = "INACTIVE";

// Black Leopard
const string BLACK_LEOPARD_ACTIVE = "BLACK_LEOPARD_ACTIVE";
const string BLACK_LEOPARD_DESTROYED = "EFFECT";
const string BLACK_LEOPARD_INACTIVE = "INACTIVE";
const string BLACK_LEOPARD_IDLE = "BLACK_LEOPARD_IDLE";
const string BLACK_LEOPARD_JUMP = "BLACK_LEOPARD_JUMP";

// Vampire Bat
const string VAMPIRE_BAT_ACTIVE = "VAMPIRE_BAT_ACTIVE";
const string VAMPIRE_BAT_DESTROYED = "EFFECT";
const string VAMPIRE_BAT_INACTIVE = "INACTIVE";

// Fish man
const string FISHMAN_ACTIVE = "FISHMAN_ACTIVE";
const string FISHMAN_DESTROYED = "EFFECT";
const string FISHMAN_INACTIVE = "INACTIVE";
const string FISHMAN_JUMP = "FISHMAN_JUMP";
const string FISHMAN_HIT = "FISHMAN_HIT";

// Boss (Phantom Bat)
const string BOSS_ACTIVE = "BOSS_ACTIVE";
const string BOSS_DESTROYED = "EFFECT_2";
const string BOSS_INACTIVE = "INACTIVE";
const string BOSS_HURT = "EFFECT";

// Fire ball
const string FIREBALL = "FIREBALL";

// Bubbles
const string BUBBLES = "BUBBLES";

// Break wall
const string NORMAL = "NORMAL";
const string BREAK = "BREAK";
#pragma endregion

#pragma region Animation 
// Animation Delay
#define SPARK_ANI_TIME_DELAY		100
#define EFFECT_ANI_TIME_DELAY		300
#define EFFECT_2_ANI_TIME_DELAY		300
#define POWER_ANI_TIME_DELAY		450
#define STAIR_WALK_ANI_TIME_DELAY	200
#define DEFLECT_ANI_TIME_DELAY		600
#define HIT_ANI_TIME_DELAY			300
#define DOOR_2_OPEN_ANI_TIME_DELAY	5000
#define FISHMAN_HIT_ANI_TIME_DELAY	1000
#pragma endregion

////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region define Properties

// Simon
constexpr float SIMON_HP = 16;
constexpr float SIMON_ENERGY = 5;
constexpr float SIMON_WALKING_SPEED = 0.13f;
constexpr float SIMON_WALKING_SPEED_LOWER = 0.05f;
constexpr float SIMON_JUMP_SPEED_Y = 0.55f;
constexpr float SIMON_GRAVITY = 0.002f;
constexpr float SIMON_GRAVITY_LOWER = 0.001f;
constexpr float SIMON_SPEED_Y_LOWER_ZONE = 0.2f;
constexpr float SIMON_STAIR_SPEED_X = 0.08f;
constexpr float SIMON_STAIR_SPEED_Y = 0.08f;
constexpr float SIMON_UNTOUCHABLE_TIME = 3000;
constexpr float SIMON_INVISIBILITY_TIME = 4000;
constexpr float SIMON_DEAD_TIME = 3000;
constexpr float SIMON_DEFLECT_SPEED_X = 0.15f;
constexpr float SIMON_DEFLECT_SPEED_Y = 0.3f;

// Item
constexpr float ITEM_FALLING_SPEED_X = 0.12f;
constexpr float ITEM_FALLING_SPEED_X_VARIATION = 0.01f;
constexpr float ITEM_SMALLHEART_FALLING_SPEED_Y = 0.1f;
constexpr float ITEM_FALLING_SPEED_Y = 0.12f;
constexpr float ITEM_FALLING_SPEED = 0.1f;
constexpr float ITEM_TIME_DESTROYED = 5000;
constexpr float ITEM_CROSS_EFFECT_TIME = 1000;
constexpr float ITEM_DOUBLE_SHOT_EFFECT_TIME = 10000;
constexpr float ITEM_TRIPLE_SHOT_EFFECT_TIME = 10000;

// SubWeapons
constexpr float WEAPONS_DAGGER_SPEED = 0.3f;

constexpr float WEAPONS_AXE_SPEED_X = 0.2f;
constexpr float WEAPONS_AXE_SPEED_Y = 0.5f;
constexpr float WEAPONS_AXE_GRAVITY = 0.001f;

constexpr float WEAPONS_HOLY_WATER_SPEED_X = 0.25f;
constexpr float WEAPONS_HOLY_WATER_SPEED_Y = 0.1f;
constexpr float WEAPONS_HOLY_WATER_GRAVITY = 0.001f;
constexpr float WEAPONS_HOLY_WATER_TIME_EFFECT = 1000;

constexpr float WEAPONS_BOOMERANG_SPEED = 0.5f;
constexpr float WEAPONS_BOOMERANG_TURNBACK_SPEED = 0.01f;

constexpr float WEAPONS_STOP_WATCH_TIME = 2000;

// Zombie
constexpr float ZOMBIE_WALKING_SPEED = 0.1f;
constexpr float ZOMBIE_RESPAWN_TIME = 5000;
constexpr float ZOMBIE_GRAVITY = 0.002f;

// Black Leopard
constexpr float BLACK_LEOPARD_RUNNING_SPEED_X = 0.3f;
constexpr float BLACK_LEOPARD_RUNNING_SPEED_Y = 0.2f;
constexpr float BLACK_LEOPARD_GRAVITY = 0.001f;
constexpr float BLACK_LEOPARD_RESPAWN_TIME = 20000;

// Vampire Bat
constexpr float VAMPIRE_BAT_FLYING_SPEED_X = 0.12f;
constexpr float VAMPIRE_BAT_FLYING_SPEED_Y = 0.1f;
constexpr float VAMPIRE_BAT_SPEED_VARIATION = 0.004f;
constexpr float VAMPIRE_BAT_RESPAWN_TIME = 5000;

// Bubbles
constexpr float BUBBLES_SPEED_X = 0.07f;
constexpr float BUBBLES_SPEED_Y = 0.1f;
constexpr float BUBBLES_SPEED_X2 = 0.03f;
constexpr float BUBBLES_SPEED_Y2 = 0.2f;
constexpr float BUBBLES_GRAVITY = 0.0005f;
constexpr float BUBBLES_TIME = 1000;

// Fire ball
constexpr float FIREBALL_SPEED = 0.13f;

// Fish man
constexpr float FISHMAN_JUMP_SPEED_Y = 0.7f;
constexpr float FISHMAN_GRAVITY = 0.0015f;
constexpr float FISHMAN_WALKING_SPEED_X = 0.1f;
constexpr float FISHMAN_RESPAWN_TIME = 3000;

// Boss
constexpr float BOSS_HP = 16;
constexpr float BOSS_DEFAULT_TIME_TO_FLY = 1000;
constexpr float BOSS_FAST_TIME_TO_FLY = 750;
constexpr float BOSS_STOP_TIME_WAITING = 1500;

// Wall pieces
constexpr float	WALLPIECES_GRAVITY = 0.0005f;
constexpr float WALLPIECES_TIME = 2000;

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region BBox Size

// Simon
#define SIMON_BBOX_WIDTH 30
#define SIMON_BBOX_HEIGHT 62

// Ground
#define GROUND_BBOX_WIDTH 32
#define GROUND_BBOX_HEIGHT 32 

// Candle
#define LARGE_CANDLE_BBOX_WIDTH			32
#define LARGE_CANDLE_BBOX_HEIGHT			64

#define CANDLE_BBOX_WIDTH		16
#define CANDLE_BBOX_HEIGHT	32

// Whip
#define LONG_CHAIN_BBOX_WIDTH 80
#define WHIP_BBOX_WIDTH 55
#define WHIP_BBOX_HEIGHT 20 

// Large Heart
#define LARGE_HEART_BBOX_WIDTH 24
#define LARGE_HEART_BBOX_HEIGHT 20

// Chain
#define CHAIN_BBOX_WIDTH 32
#define CHAIN_BBOX_HEIGHT 32

// SubWeapons
#define WEAPONS_HOLY_WATER_BBOX_WIDTH			32
#define WEAPONS_HOLY_WATER_BBOX_HEIGHT			26

#define WEAPONS_DAGGER_BBOX_WIDTH			32
#define WEAPONS_DAGGER_BBOX_HEIGHT			18

#define WEAPONS_AXE_BBOX_WIDTH			30
#define WEAPONS_AXE_BBOX_HEIGHT			28

#define WEAPONS_BOOMERANG_BBOX_WIDTH			28
#define WEAPONS_BOOMERANG_BBOX_HEIGHT			28

// Stair
#define STAIR_BBOX_WIDTH			32
#define STAIR_BBOX_HEIGHT			32

// Door
#define DOOR_BBOX_WIDTH				32
#define DOOR_BBOX_HEIGHT			96

// Change Scene Object
#define CHANGE_SCENE_BBOX_WIDTH		32
#define CHANGE_SCENE_BBOX_HEIGHT	32

// Zombie
#define ZOMBIE_BBOX_WIDTH			10
#define ZOMBIE_BBOX_HEIGHT			60
#define ZOMBIE_ACTIVE_BBOX_WIDTH		    200
#define ZOMBIE_ACTIVE_BBOX_HEIGHT			200

// Black Leopard
#define BLACK_LEOPARD_BBOX_WIDTH			10
#define BLACK_LEOPARD_BBOX_HEIGHT			32
#define BLACK_LEOPARD_ACTIVE_BBOX_WIDTH		100
#define BLACK_LEOPARD_ACTIVE_BBOX_HEIGHT	200

// Vampire Bat
#define VAMPIRE_BAT_BBOX_WIDTH			10
#define VAMPIRE_BAT_BBOX_HEIGHT			10
#define VAMPIRE_BAT_ACTIVE_BBOX_WIDTH			250 
#define VAMPIRE_BAT_ACTIVE_BBOX_HEIGHT			200

// Fire ball
#define FIREBALL_BBOX_WIDTH				14
#define FIREBALL_BBOX_HEIGHT			20

// Fish man
#define FISHMAN_BBOX_WIDTH			10
#define FISHMAN_BBOX_HEIGHT			60
#define FISHMAN_ACTIVE_BBOX_WIDTH			200
#define FISHMAN_ACTIVE_BBOX_HEIGHT			200

// Boss
#define BOSS_BBOX_WIDTH				70
#define BOSS_BBOX_HEIGHT			46
#define BOSS_ACTIVE_BBOX_WIDTH		50
#define BOSS_ACTIVE_BBOX_HEIGHT		400
#define BOSS_RECT_RANDOMSPOT_BBOX_WIDTH	150
#define BOSS_RECT_RANDOMSPOT_BBOX_HEIGHT 150 

#define ENEMY_DEFAULT_BBOX_WIDTH			32
#define ENEMY_DEFAULT_BBOX_HEIGHT			32

// Water
#define	WATER_BBOX_WIDTH			512
#define WATER_BBOX_HEIGHT			32

#pragma endregion

#pragma region ID objects to load from file

const string GROUND = "GROUND";
const string HIDDEN = "HIDDEN";
const string HIDDENMONEY = "HIDDENMONEY";
const string STAIR = "STAIR";
const string DOOR = "DOOR";
const string ZOMBIE = "ZOMBIE";
const string BLACK_LEOPARD = "BLACK_LEOPARD";
const string VAMPIRE_BAT = "VAMPIRE_BAT";
const string FISHMAN = "FISHMAN";
const string BOSS = "BOSS";
const string CHANGE_SCENE_OBJECT = "CHANGE_SCENE_OBJECT";
const string WATER = "WATER";
const string BREAKWALL = "BREAKWALL";

#pragma endregion

#define NOW GetTickCount();
