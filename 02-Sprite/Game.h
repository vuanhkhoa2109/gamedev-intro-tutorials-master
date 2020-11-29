#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Const.h"

#define KEYBOARD_BUFFER_SIZE 1024
/*
Abstract class to define keyboard event handlers
*/
class KeyEventHandler
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

typedef KeyEventHandler* LPKEYEVENTHANDLER;

class Game
{

#pragma region DX2D
	static Game* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	ID3DXFont* font;
#pragma endregion DX2D

public:
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void Init(HWND hWnd);
	void Draw(int nx, float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int width, int height, int alpha = 255);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int width, int height, int alpha = 255);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	ID3DXFont* GetFont() {
		return this->font;
	}
	void DrawUIText(std::string text, RECT bound);
	void DrawHud(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mw,			// move width
		float mh,			// move height 
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sw,
		float sh,
		float& t,
		float& nx,
		float& ny);

	static bool AABB(float objectLeft, float objectTop, float objectRight, float objectBottom, float otherLeft, float otherTop, float otherRight, float otherBottom);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }

	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }

	D3DXVECTOR2 GetCamPos() { D3DXVECTOR2 cam; cam.x = this->cam_x; cam.y = this->cam_y; return cam; };

	static Game* GetInstance();

	~Game();
};
