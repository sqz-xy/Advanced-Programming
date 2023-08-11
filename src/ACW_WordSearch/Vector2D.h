#pragma once

/// <summary>
/// A two dimensional vector containing an X and Y value
/// </summary>
struct Vector2D
{
public:
	explicit Vector2D(const int p_x, const int p_y);
	explicit Vector2D(const Vector2D& p_rhs);
	~Vector2D();

	Vector2D& operator=(const Vector2D& p_vector2D);

	int x, y;
};