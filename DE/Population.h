#pragma once

#include "Agent.h"
#include <algorithm>
#include <vector>

// 种群
template<size_t N, typename T = double>
class Population
{
public:
	Population(int = 10);
	Population(const std::vector<T>&, const std::vector<T>&, int = 10);
	Population(const Population&);

	Agent<N, T>& operator[](int);
	Agent<N, T> operator[](int) const;
	Agent<N, T>& at(int);
	Agent<N, T> at(int) const;

	// 进化
	template<typename FuncTF, typename FuncF, typename FuncCR>
	Population evolution(FuncTF, FuncF, FuncCR);
	// 计算种群中每个个题是适应度
	template<typename FuncTF>
	void fit(FuncTF);
	// 获取种群中最好适应度
	T get_best_fit() const;
	// 获取种群中最差适应度
	T get_worst_fit() const;

private:
	// 种群大小
	int _np;
	// 种群中的个体
	std::vector<Agent<N, T>> _agents;
	// 每个个体的适应度
	std::vector<T> _fit;
	// 最好适应度和最差适应度
	T _fit_min, _fit_max;

	// 变异
	template<typename FuncF>
	Population variation(FuncF) const;
	// 交叉
	template<typename FuncCR>
	Population cross(const Population&, FuncCR) const;
	// 选择
	template<typename FuncTF>
	Population selection(const Population&, FuncTF) const;
};

template<size_t N, typename T>
inline Population<N, T>::Population(int np) :
	_np(np), _agents(np), _fit(np),
	_fit_min(std::numeric_limits<T>::max()),
	_fit_max(std::numeric_limits<T>::min())
{ }

template<size_t N, typename T>
inline Population<N, T>::Population(const std::vector<T>& l, const std::vector<T>& u, int np) :
	_np(np), _agents(np), _fit(np),
	_fit_min(std::numeric_limits<T>::max()),
	_fit_max(std::numeric_limits<T>::min())
{
	for (auto i = 0; i < np; i++)
		_agents[i] = Agent<N, T>(l, u);
}

template<size_t N, typename T>
inline Population<N, T>::Population(const Population& p) :
	_np(p._np), _agents(p._agents), _fit(p._fit), _fit_min(p._fit_min), _fit_max(p._fit_max)
{ }

template<size_t N, typename T>
inline T Population<N, T>::get_best_fit() const
{
	return _fit_min;
}

template<size_t N, typename T>
inline T Population<N, T>::get_worst_fit() const
{
	return _fit_max;
}

template<size_t N, typename T>
inline Agent<N, T>& Population<N, T>::operator[](int i)
{
	return at(i);
}

template<size_t N, typename T>
inline Agent<N, T> Population<N, T>::operator[](int i) const
{
	return at(i);
}

template<size_t N, typename T>
inline Agent<N, T>& Population<N, T>::at(int i)
{
	return _agents[i];
}

template<size_t N, typename T>
inline Agent<N, T> Population<N, T>::at(int i) const
{
	return _agents[i];
}

// 变异因子f
template<size_t N, typename T>
template<typename FuncF>
inline Population<N, T> Population<N, T>::variation(FuncF f) const
{
	Population res(_np);
	for (auto i = 0; i < _np; i++)
	{
		auto a = rand() % _np, b = rand() % _np, c = rand() % _np;
		while (b == a) b = rand() % _np;
		while (c == a || c == b) c = rand() % _np;
		if (_fit[a] < _fit[b]) std::swap(a, b);
		if (_fit[a] < _fit[c]) std::swap(a, c);
		if (_fit[b] < _fit[c]) std::swap(b, c);
		res[i] = _agents[a] + (_agents[b] - _agents[c]) * f(_fit[a], _fit[b], _fit[c]);
	}
	return res;
}

// 交叉因子cr
template<size_t N, typename T>
template<typename FuncCR>
inline Population<N, T> Population<N, T>::cross(const Population& p, FuncCR cr) const
{
	Population res(_np);
	for (auto i = 0; i < _np; i++)
		for (auto j = 0; j < N; j++)
			res[i][j] = (T)rand() / RAND_MAX < cr(_fit[i], _fit_min, _fit_max) ?
				_agents[i][j] : p[i][j];
	return res;
}

// 目标函数tf
template<size_t N, typename T>
template<typename FuncTF>
inline Population<N, T> Population<N, T>::selection(const Population& p, FuncTF tf) const
{
	Population res;
	for (auto i = 0; i < _np; i++)
		res[i] = tf(_agents[i]) < tf(p[i]) ? _agents[i] : p[i];
	return res;
}

template<size_t N, typename T>
template<typename FuncTF, typename FuncF, typename FuncCR>
inline Population<N, T> Population<N, T>::evolution(FuncTF tf, FuncF f, FuncCR cr)
{
	//for (auto i = 0; i < _np; i++)
	//{
	//	for (auto j = 0; j < N; j++)
	//		printf("%lf ", _agents[i][j]);
	//	printf(": %lf\n", _fit[i]);
	//}
	//printf("\n");
	return selection(cross(variation(f), cr), tf);
}

template<size_t N, typename T>
template<typename FuncTF>
inline void Population<N, T>::fit(FuncTF tf)
{
	for (auto i = 0; i < _np; i++)
	{
		_fit[i] = tf(_agents[i]);
		_fit_min = std::min(_fit_min, _fit[i]);
		_fit_max = std::max(_fit_max, _fit[i]);
	}
}
