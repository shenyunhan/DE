#pragma once

#include <algorithm>
#include <vector>

// 个体，N为数据维数，T为数据类型
template<size_t N, typename T = double>
class Agent
{
public:
	Agent();

	T& operator[](int);
	T operator[](int) const;
	T& at(int);
	T at(int) const;

	Agent operator+(const Agent& rhs) const;
	Agent operator-(const Agent& rhs) const;
	Agent operator*(T rhs) const;
	Agent operator/(T rhs) const;

private:
	std::vector<T> _x;
};

template<size_t N, typename T>
inline Agent<N, T>::Agent() : _x(N, 0)
{ }

template<size_t N, typename T>
inline T& Agent<N, T>::operator[](int i)
{
	return at(i);
}

template<size_t N, typename T>
inline T Agent<N, T>::operator[](int i) const
{
	return at(i);
}

template<size_t N, typename T>
inline T& Agent<N, T>::at(int i)
{
	return _x[i];
}

template<size_t N, typename T>
inline T Agent<N, T>::at(int i) const
{
	return _x[i];
}

template<size_t N, typename T>
inline Agent<N, T> Agent<N, T>::operator+(const Agent& rhs) const
{
	Agent res;
	for (auto i = 0; i < N; i++)
		res[i] = _x[i] + rhs[i];
	return res;
}

template<size_t N, typename T>
inline Agent<N, T> Agent<N, T>::operator-(const Agent& rhs) const
{
	Agent res;
	for (auto i = 0; i < N; i++)
		res[i] = _x[i] - rhs[i];
	return res;
}

template<size_t N, typename T>
inline Agent<N, T> Agent<N, T>::operator*(T rhs) const
{
	Agent res;
	for (auto i = 0; i < N; i++)
		res[i] = _x[i] * rhs;
	return res;
}

template<size_t N, typename T>
inline Agent<N, T> Agent<N, T>::operator/(T rhs) const
{
	Agent res;
	for (auto i = 0; i < N; i++)
		res[i] = _x[i] / rhs;
	return res;
}
