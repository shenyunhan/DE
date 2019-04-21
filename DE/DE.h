#pragma once

#include "Agent.h"
#include "Population.h"

// 差分进化
template<size_t N, typename T = double,
	typename FuncTF = T (*)(const Agent<N, T>&),
	typename FuncF = T (*)(T, T, T),
	typename FuncCR = T (*)(T, T, T)>
class DE
{
public:
	static constexpr T _eps = 1e-8;

	DE(FuncTF tf, FuncF f = [](T fb, T fm, T fw)
	{
		return 0.1 + 0.8 * (fm - fb) / (fw - fb + DE<N, T, FuncTF, FuncF, FuncCR>::_eps);
	}, FuncCR cr = [](T fi, T fmin, T fmax)
	{
		return 0.1 + 0.5 * (fi - fmin) / (fmax - fmin + DE<N, T, FuncTF, FuncF, FuncCR>::_eps);
	}, int np = 8 * N, int g = 30);

	// 进行迭代，传入参数为每个个体每一维的上下界
	Population<N, T> solve(Agent<N> (*generator)());

private:
	
	FuncTF _tf; // 目标函数
	FuncF _f; // 变异因子
	FuncCR _cr; // 交叉因子
	int _np, _g; // 种群数量，最大迭代次数

	int sgn(T) const;
};

template<size_t N, typename T, typename FuncTF, typename FuncF, typename FuncCR>
inline DE<N, T, FuncTF, FuncF, FuncCR>::DE(FuncTF tf, FuncF f, FuncCR cr, int g, int np) :
	_tf(tf), _f(f), _cr(cr), _np(np), _g(g)
{ }

template<size_t N, typename T, typename FuncTF, typename FuncF, typename FuncCR>
inline Population<N, T> DE<N, T, FuncTF, FuncF, FuncCR>::solve(Agent<N> (*generator)())
{
	Population<N, T> res(generator);
	for (auto g = 0; g < _g; g++)
	{
		res.fit(_tf);
		if (sgn(res.get_best_fit() - res.get_worst_fit()) == 0) break;
		res = res.evolution(_tf, _f, _cr);
	}
	return res;
}

template<size_t N, typename T, typename FuncTF, typename FuncF, typename FuncCR>
inline int DE<N, T, FuncTF, FuncF, FuncCR>::sgn(T x) const
{
	return x < -_eps ? -1 : x > _eps ? 1 : 0;
}
