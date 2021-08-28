#pragma once
// a 2d math vector template

#include <math.h>

#define PI 3.1415926

template <class T = float>
class vec2d
{
public:
	T x, y;

public:
	vec2d() : x(0), y(0)
	{}

	vec2d(T x_in, T y_in) : x(x_in), y(y_in)
	{}

	vec2d(float angle)
	{
		x = sin(angle);
		y = cos(angle);
	}

	vec2d<T> operator+(const vec2d<T>& rhs) const // left + right
	{
		return vec2d<T>(x + rhs.x, y + rhs.y);
	}

	vec2d<T> operator+=(const vec2d<T>& rhs) // left = left + right
	{
		*this = *this + rhs;
		return *this;
	}

	vec2d<T> operator-(const vec2d<T>& rhs) const // left - right
	{
		return vec2d<T>(x - rhs.x, y - rhs.y);
	}

	vec2d<T> operator-=(const vec2d<T>& rhs) // left = left - right
	{
		*this = *this - rhs;
		return *this;
	}

	vec2d<T> operator*(float rhs) const //left * right
	{
		return vec2d<T>(x * rhs, y * rhs);
	}

	vec2d<T> operator*=(float rhs) // left = left * right
	{
		*this = *this * rhs;
		return *this;
	}

	// returns the length of the vector
	T getLength() const
	{
		return sqrt(getLengthSq());
	}

	// returns the square of the length of the vector
	T getLengthSq() const
	{
		return x * x + y * y;
	}

	// normalizezes the vector
	vec2d<T> normalize()
	{
		return *this = getNormalized();
	}

	// returns a normalized vector
	vec2d<T> getNormalized() const
	{
		const float len = getLength();
		if (len != 0)
			return *this * (1.0f / len);
		return *this;
	}

	// rounds the vector to the nearest whole number
	vec2d<int> round()
	{
		return vec2d<int>((int)x, (int)y);
	}

	vec2d<T> roundf()
	{
		return vec2d<T>((int)x, (int)y);
	}

	// returns a vector with the combined lowest values
	vec2d<T> Min(const vec2d& rhs) const
	{
		return vec2d<T>(x < rhs.x ? x : rhs.x, y < rhs.y ? y : rhs.y);
	}

	// returns a vector with the combined highest values
	vec2d<T> Max(const vec2d& rhs) const
	{
		return vec2d<T>(x > rhs.x ? x : rhs.x, y > rhs.y ? y : rhs.y);
	}

	// makes the vector the absolute value of itself
	vec2d<T> abs()
	{
		*this = getAbs();
		return *this;
	}

	// returns a vector with the aboslute value of the original
	vec2d<T> getAbs()
	{
		vec2d<T> temp = *this;

		if (temp.x < 0)
			temp.x *= -1;
		if (temp.y < 0)
			temp.y *= -1;

		return temp;
	}
};

