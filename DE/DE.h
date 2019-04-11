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
	DE(FuncTF, FuncF = [](T fb, T fm, T fw) { return 0.1 + 0.8 * (fm - fb) / (fw - fb + _eps); },
		FuncCR = [](T fi, T fmin, T fmax) { 0.1 + 0.5 * (fi - fmin) / (fmax - fmin + _eps); },
		int = 8 * N, int = 30, T = 1e-8);

	// 进行迭代，传入参数为每个个体每一维的上下界
	Population<N, T> solve(const std::vector<T>&, const std::vector<T>&);

private:
	// 目标函数
	FuncTF _tf;
	// 变异因子
	FuncF _f;
	// 交叉因子
	FuncCR _cr;
	// 种群数量，最大迭代次数
	int _np, _g;
	// 最小极差
	T _eps;

	int sgn(T) const;
};

template<size_t N, typename T, typename FuncTF, typename FuncF, typename FuncCR>
inline DE<N, T, FuncTF, FuncF, FuncCR>::DE(FuncTF tf, FuncF f, FuncCR cr, int g, int np, T eps) :
	_tf(tf), _f(f), _cr(cr), _np(np), _g(g), _eps(eps)
{ }

template<size_t N, typename T, typename FuncTF, typename FuncF, typename FuncCR>
inline Population<N, T> DE<N, T, FuncTF, FuncF, FuncCR>::solve(const std::vector<T>& l, const std::vector<T>& u)
{
	Population<N, T> res(l, u);
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
