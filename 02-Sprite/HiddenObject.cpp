#include "HiddenObject.h"

void HiddenObject::Render()
{
	RenderBoundingBox();
}

void HiddenObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width;
	b = y + height;
}
