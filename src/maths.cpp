#include <math.h>
#include "maths.h"


Vector2D::Vector2D()
{
	this->x = 0;
	this->y = 0;
}


Vector2D::Vector2D(PERSISION x, PERSISION y)
{
	this->x = x;
	this->y = y;
}


Vector2D operator + (const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.x + b.x, a.y + b.y);
}


Vector2D operator - (const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.x - b.x, a.y - b.y);
}


PERSISION operator * (const Vector2D& a, const Vector2D& b)
{
	return a.x * b.x + a.y * b.y;
}


Vector2D Vector2D::operator * (PERSISION c)
{
	return Vector2D(x * c, y * c);
}


Vector2D Vector2D::operator / (PERSISION c)
{
	return Vector2D(x / c, y / c);
}


SV2D::SV2D() { x = 0; y = 0; }


SV2D::SV2D(PERSISION x, PERSISION y) : x(x), y(y) {}


Vector2D rotate(Vector2D& a, PERSISION rot)
{
	return Vector2D(a.x * cos(rot) - a.y * sin(rot), a.x * sin(rot) + a.y * cos(rot));
}