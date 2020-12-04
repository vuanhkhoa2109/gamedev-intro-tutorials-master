#pragma once
#include "GameObject.h"

// Trigger object ?? nh?n bi?t vi?c chuy?n scene khi xét va ch?m v?i Simon.
class ChangeSceneBlock : public GameObject
{
	int IDNextScene;

public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL) {}
	virtual void Render() {}

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetIDNextScene(int x) { this->IDNextScene = x; }
	int GetIDNextScene() { return this->IDNextScene; }
};

