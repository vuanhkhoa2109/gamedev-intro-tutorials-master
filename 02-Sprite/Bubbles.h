#pragma once

#include <vector>
#include "GameObject.h"

class Bubble : public GameObject
{
public:
	Bubble();
	~Bubble();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

typedef Bubble* LPBUBBLE;

// V� m?i c?m c� 3 Bubble n�n t?o class Bubbles ?? qu?n l�
class Bubbles
{
	DWORD startTime = 0;

public:
	vector<LPBUBBLE> bubbles;
	Bubbles(float x, float y);
	~Bubbles();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

	DWORD GetStartTimeRender() { return startTime; }
	void SetStartTimeRender(DWORD x) { startTime = x; }
};