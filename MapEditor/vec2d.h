#pragma once
// a 2d math vector template

#include <math.h>

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

	vec2d(const vec2d<T>& copy)
	{
		*this = copy;
	}

	vec2d<T> operator=(const vec2d<T>& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
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

	T getLength() const
	{
		return sqrt(getLengthSq());
	}

	T getLengthSq() const
	{
		return x * x + y * y;
	}

	vec2d<T> normalize()
	{
		return *this = getNormalized();
	}

	vec2d<T> getNormalized() const
	{
		const float len = getLength();
		if (len != 0)
			return *this * (1.0f / len);
		return *this;
	}

	vec2d<T> round()
	{
		return vec2d<T>((int)x, (int)y);
	}
};

