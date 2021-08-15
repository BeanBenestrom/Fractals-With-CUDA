#pragma once

#include "settings.h"


struct Vector2D
{
	PERSISION x, y;

	Vector2D();
	Vector2D(PERSISION x, PERSISION y);
	friend Vector2D operator + (const Vector2D& a, const Vector2D& b);
	friend Vector2D operator - (const Vector2D& a, const Vector2D& b);
	friend PERSISION operator * (const Vector2D& a, const Vector2D& b);
	Vector2D operator * (PERSISION c);
	Vector2D operator / (PERSISION c);
};


struct SV2D
{
	PERSISION x, y;

	SV2D();
	SV2D(PERSISION x, PERSISION y);
};


Vector2D rotate(Vector2D& a, PERSISION rot);
