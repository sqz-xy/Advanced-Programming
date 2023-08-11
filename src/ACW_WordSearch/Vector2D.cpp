#include "Vector2D.h"

Vector2D::Vector2D(const int p_x, const int p_y) : x(p_x), y(p_y) {}

Vector2D::Vector2D(const Vector2D& p_rhs) : x(p_rhs.x), y(p_rhs.y) {}

Vector2D::~Vector2D() {}

Vector2D& Vector2D::operator=(const Vector2D& p_vector2D)
{
	if (&p_vector2D != this)
	{
		x = p_vector2D.x;
		y = p_vector2D.y;
	}

	return *this;
}
