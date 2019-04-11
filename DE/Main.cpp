#define _CRT_SECURE_NO_WARNINGS
#include "Agent.h"
#include "DE.h"
#include <cstdio>
const int _ATTR = 3;
const int MAXN = 105;

int n;
Agent<_ATTR> p[MAXN];

inline double sqr(double x)
{
	return x * x;
}

template<size_t N>
double dist(const Agent<N>& a, const Agent<N>& b)
{
	double res = 0;
	for (auto i = 0; i < N; i++)
		res += sqr(a[i] - b[i]);
	return sqrt(res);
}

// 目标函数
double tf(const Agent<_ATTR>& agent)
{
	double res = 0;
	for (int i = 0; i < n; i++)
		res = std::max(res, dist(agent, p[i]));
	return res;
}

double f(double fb, double fm, double fw)
{
	return 0.5;
}

double cr(double fi, double fmin, double fmax)
{
	return 0.5;
}

int main()
{
	scanf("%d", &n);
	std::vector<double> l(_ATTR), u(_ATTR);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < _ATTR; j++)
		{
			scanf("%lf", &p[i][j]);
			l[j] = std::min(l[j], p[i][j]);
			u[j] = std::max(u[j], p[i][j]);
		}
	DE<_ATTR> de(tf, f, cr, 300);
	auto res = de.solve(l, u);
	res.fit(tf);
	printf("%lf\n", res.get_best_fit());
	return 0;
}