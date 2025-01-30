#pragma once

#include "corecrt_math.h"
// A dimensional Vector.
template<class NumberType>
struct Vector2
{
	NumberType m_x;
	NumberType m_y;

	// Multiplies vector by a one-dimensional scalar.
	Vector2 operator*(float right)
	{
		return Vector2{ m_x * right, m_y * right };
	}

	// Calculates a vector passing from A to B.
	Vector2 operator-(Vector2 b)
	{
		return Vector2{this->m_x - b.m_x, this->m_y - b.m_y};
	}

	// Returns the squared length of this vector.
	NumberType GetSquareLength()
	{
		return m_x * m_x + m_y * m_y;
	}

	// Returns a vector with the same component proportions
	// but a length of one.
	Vector2 GetNormalized()
	{
		// Calculate the exact length
		float length = sqrtf(GetSquareLength());

		// Account for a length of zero
		if (length == 0)
			return Vector2{ 0,0 };
		
		return Vector2{ m_x / length, m_y / length };
	}
};

