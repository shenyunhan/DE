#pragma once

#include "Agent.h"
#include "Population.h"

// ��ֽ���
template<size_t N, typename T = double,
	typename FuncTF = T (*)(const Agent<N, T>&),
	typename FuncF = T (*)(T, T, T),
	typename FuncCR = T (*)(T, T, T)>
class DE
{
public:
	static constexpr T _eps = 1e-8;

	DE(int np, int g, FuncTF tf, FuncF f = [](T fb, T fm, T fw)
	{
		return 0.1 + 0.8 * (fm - fb) / (fw - fb + DE<N, T, FuncTF, FuncF, FuncCR>::_eps);
	}, FuncCR cr = [](T fi, T fmin, T fmax)
	{
		return 0.1 + 0.5 * (fi - fmin) / (fmax - fmin + DE<N, T, FuncTF, FuncF, FuncCR>::_eps);
	});

	// ���е������������Ϊÿ������ÿһά�����½�
	Population<N, T> solve(Agent<N> (*generator)());

private:
	int _np, _g; // ��Ⱥ����������������
	FuncTF _tf; // Ŀ�꺯��
	FuncF _f; // ��������
	FuncCR _cr; // ��������

	int sgn(T) const;
};

template<size_t N, typename T, typename FuncTF, typename FuncF, typename FuncCR>
inline DE<N, T, FuncTF, FuncF, FuncCR>::DE(int g, int np, FuncTF tf, FuncF f, FuncCR cr) :
	_np(np), _g(g), _tf(tf), _f(f), _cr(cr)
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
	res.fit(_tf);
	/*auto best = res.get_best_agent();
	for (auto i = 0; i < 9; i++)
		std::cout << best[i] << " ";
	std::cout << std::endl;*/
	return std::move(res);
}

template<size_t N, typename T, typename FuncTF, typename FuncF, typename FuncCR>
inline int DE<N, T, FuncTF, FuncF, FuncCR>::sgn(T x) const
{
	return x < -_eps ? -1 : x > _eps ? 1 : 0;
}
