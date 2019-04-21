#pragma once
#include "Global.h"

template<size_t N = 3, typename T = double>
struct Point
{
	T x[N];

	T& operator[](int i);
	T operator[](int i) const;
};

template<size_t N, typename T>
inline T& Point<N, T>::operator[](int i)
{
	return x[i];
}

template<size_t N, typename T>
inline T Point<N, T>::operator[](int i) const
{
	return x[i];
}

template<size_t N, typename T>
using Vector = Point<N, T>;

template<size_t N, typename T>
Vector<N, T> operator+(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
{
	Vector<N, T> res;
	for (auto i = 0; i < N; i++)
		res[i] = lhs[i] + rhs[i];
	return res;
}

template<size_t N, typename T>
Vector<N, T> operator-(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
{
	Vector<N, T> res;
	for (auto i = 0; i < N; i++)
		res[i] = lhs[i] - rhs[i];
	return res;
}

template<size_t N, typename T>
Vector<N, T> operator*(const Vector<N, T>& lhs, T rhs)
{
	Vector<N, T> res;
	for (auto i = 0; i < N; i++)
		res[i] = lhs[i] * rhs;
	return res;
}

template<size_t N, typename T>
Vector<N, T> operator/(const Vector<N, T>& lhs, T rhs)
{
	Vector<N, T> res;
	for (auto i = 0; i < N; i++)
		res[i] = lhs[i] / rhs;
	return res;
}

template<size_t N, typename T>
T dist(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
{
	T res = 0;
	for (auto i = 0; i < N; i++)
		res += sqr(lhs[i] - rhs[i]);
	return sqrt(res);
}