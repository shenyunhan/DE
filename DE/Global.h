#pragma once
#include <cmath>

const double KB = 1.38e-23;
const double PI = std::acos(-1);

template<typename T>
inline T sqr(T x)
{
	return x * x;
}

template<typename T>
inline T cub(T x)
{
	return x * x * x;
}

template<typename T>
inline T frand(T mini, T maxi)
{
	return mini + (T)rand() / RAND_MAX * (maxi - mini);
}
