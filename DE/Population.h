#pragma once

#include "Agent.h"
#include <algorithm>
#include <vector>
#include <cassert>

// 种群
template<size_t N, typename T = double>
class Population
{
public:
	Population(int np = 10);
	Population(Agent<N> (*generator)(), int np = 10);
	Population(const Population& p);

	Agent<N, T>& operator[](int i);
	Agent<N, T> operator[](int i) const;
	Agent<N, T>& at(int i);
	Agent<N, T> at(int i) const;

	// 进化
	template<typename FuncTF, typename FuncF, typename FuncCR>
	Population evolution(FuncTF tf, FuncF f, FuncCR cr);
	// 计算种群中每个个体的适应度
	template<typename FuncTF>
	void fit(FuncTF tf);
	// 获取种群中最好适应度
	T get_best_fit() const;
	// 获取种群中最差适应度
	T get_worst_fit() const;

	Agent<N, T> get_best_agent() const;
	Agent<N, T> get_worat_agent() const;

private:
	// 种群大小
	int _np;
	// 种群中的个体
	std::vector<Agent<N, T>> _agents;
	// 每个个体的适应度
	std::vector<T> _fit;
	// 最好适应度和最差适应度
	T _best_fit, _worst_fit;

	Agent<N, T> _best_agent, _worst_agent;

	// 变异
	template<typename FuncF>
	Population variation(FuncF cf) const;
	// 交叉
	template<typename FuncCR>
	Population cross(const Population& p, FuncCR cr) const;
	// 选择
	template<typename FuncTF>
	Population selection(const Population& p, FuncTF tf) const;
};

template<size_t N, typename T>
inline Population<N, T>::Population(int np) :
	_np(np), _agents(np), _fit(np),
	_best_fit(std::numeric_limits<T>::max()),
	_worst_fit(std::numeric_limits<T>::min())
{ }

template<size_t N, typename T>
inline Population<N, T>::Population(Agent<N> (*generator)(), int np) :
	_np(np), _agents(np), _fit(np),
	_best_fit(std::numeric_limits<T>::max()),
	_worst_fit(std::numeric_limits<T>::min())
{
	for (auto i = 0; i < np; i++)
		_agents[i] = generator();
}

template<size_t N, typename T>
inline Population<N, T>::Population(const Population& p) :
	_np(p._np), _agents(p._agents), _fit(p._fit),
	_best_fit(p._best_fit), _worst_fit(p._worst_fit),
	_best_agent(p._best_agent), _worst_agent(p._worst_agent)
{ }

template<size_t N, typename T>
inline T Population<N, T>::get_best_fit() const
{
	return _best_fit;
}

template<size_t N, typename T>
inline T Population<N, T>::get_worst_fit() const
{
	return _worst_fit;
}

template<size_t N, typename T>
inline Agent<N, T> Population<N, T>::get_best_agent() const
{
	return _best_agent;
}

template<size_t N, typename T>
inline Agent<N, T> Population<N, T>::get_worat_agent() const
{
	return _worst_agent;
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
		assert(a < _np);
		assert(b < _np);
		assert(c < _np);
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
			res[i][j] = (T)rand() / RAND_MAX < cr(_fit[i], _best_fit, _worst_fit) ?
				_agents[i][j] : p[i][j];
	return res;
}

// 目标函数tf
template<size_t N, typename T>
template<typename FuncTF>
inline Population<N, T> Population<N, T>::selection(const Population& p, FuncTF tf) const
{
	Population res(_np);
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
	assert(_agents.size() == _np);
	assert(_fit.size() == _np);
	return selection(cross(variation(f), cr), tf);
}

template<size_t N, typename T>
template<typename FuncTF>
inline void Population<N, T>::fit(FuncTF tf)
{
	for (auto i = 0; i < _np; i++)
	{
		_fit[i] = tf(_agents[i]);
		if (_fit[i] < _best_fit)
		{
			_best_fit = _fit[i];
			_best_agent = _agents[i];
		}
		if (_fit[i] > _worst_fit)
		{
			_worst_fit = _fit[i];
			_worst_agent = _agents[i];
		}
	}
}
