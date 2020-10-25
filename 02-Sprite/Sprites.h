#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include "Const.h"
#include "Game.h"

using namespace rapidxml;

using namespace std;

class Sprite
{
	string idSprite;				// Sprite ID in the sprite database

	int left;
	int top;
	int width;
	int height;

	LPDIRECT3DTEXTURE9 texture;
public:
	Sprite(string idSprite, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex);

	void Draw(int nx, float x, float y, int alpha = 255);
	void Draw(float x, float y, int alpha = 255);
};

typedef Sprite* LPSPRITE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Manage sprite database
*/
class Sprites
{
	static Sprites* __instance;

	unordered_map<string, LPSPRITE> sprites;

public:
	void Add(string idSprite, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(string idSprite);
	LPSPRITE& operator[](string idSprite) { return sprites[idSprite]; }

	static Sprites* GetInstance();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Sprite animation
*/
class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef AnimationFrame* LPANIMATION_FRAME;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Animation
{
	DWORD animStartTime;   // m?c th?i gian k? t? lúc b?t ??u render m?t animation
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;

	vector<LPANIMATION_FRAME> frames;

public:
	bool completed = false;

	Animation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }

	int GetCurrentFrame() { return this->currentFrame; }
	int GetFrameSize() { return this->frames.size(); }

	void Add(string spriteId, DWORD time = 0);
	void Render(int nx, float x, float y, int alpha = 255);
	void Render(float x, float y, int alpha = 255);

	bool IsCompleted() { return completed; }
	void SetAniStartTime(DWORD t) { animStartTime = t; }
	void Reset() { currentFrame = -1; }
	bool IsOver(DWORD dt) { return GetTickCount() - animStartTime >= dt; /*currentFrame == frames.size() - 1;*/ }

};

typedef Animation* LPANIMATION;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Animations
{
	static Animations* __instance;

	unordered_map<string, LPANIMATION> animations;

public:
	void Add(string idAni, LPANIMATION ani);
	LPANIMATION Get(string idAni);

	static Animations* GetInstance();
};

