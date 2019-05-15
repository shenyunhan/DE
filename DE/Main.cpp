#define _CRT_SECURE_NO_WARNINGS
#include "Global.h"
#include "Point.h"
#include "Agent.h"
#include "DE.h"
#include "Radar.h"
#include "ECM.h"
#include <iostream>
const int _ATTR = 3 * 3;
const int MAXN = 15;

int n_ecm = 3, n_radar;
ECM ecms[MAXN];
Radar radars[MAXN];
Point<> center;

Point<> get_point()
{
	Point<> res;
	bool flag;
	do
	{
		res[0] = frand(0.0, 400000.0), res[1] = frand(0.0, 400000.0), res[2] = frand(1000.0, 3000.0);
		flag = true;
		for (int i = 0; i < n_radar; i++)
			if (dist(radars[i].x, res) <= radars[i].R)
			{
				flag = false;
				break;
			}
	} while (flag);
	return res;
}

// 个体生成器
Agent<_ATTR> generator()
{
	auto res = Agent<_ATTR>();
	for (int i = 0; i < n_ecm; i++)
	{
		Point<> p = get_point();
		res[i * 3] = p[0], res[i * 3 + 1] = p[1], res[i * 3 + 2] = p[2];
	}
	return res;
}

// 目标函数
double tf(const Agent<_ATTR>& agent)
{
	double res = 0;
	for (int i = 0; i < n_ecm; i++)
	{
		Point<> p;
		p[0] = agent[i * 3], p[1] = agent[i * 3 + 1], p[2] = agent[i * 3 + 2];
		if (p[0] < 0 || p[0] > 400000) return 1e9;
		if (p[1] < 0 || p[1] > 400000) return 1e9;
		if (p[2] < 1000 || p[2] > 3000) return 1e9;
		for (int j = 0; j < n_radar; j++)
			if (sqr(dist(p, radars[j].x)) < radars[i].R * 1000) return 1e9;
		res -= dist(p, center);
	}
	for (int i = 0; i < n_radar; i++)
	{
		double sum = 0;
		for (int j = 0; j < n_ecm; j++)
		{
			Point<> p;
			p[0] = agent[j * 3], p[1] = agent[j * 3 + 1], p[2] = agent[j * 3 + 2];
			sum += ecms[j].getR() / dist(radars[i].x, p);
		}
		sum *= 4 * PI * radars[i].L * radars[i].Gphi * radars[i].Br;
		double R = radars[i].getR(sum);
		for (int j = 0; j < n_ecm; j++)
			res += (ecms[j].P * ecms[j].G) / (radars[i].P * radars[i].G) * (4 * PI * sqr(R) / radars[i].sigma);
	}
	return res;
}

int main()
{
	freopen("input.in", "r", stdin);
	std::cout << "己方干扰机数量：" << n_ecm << std::endl;
	for (int i = 0; i < n_ecm; i++)
	{
		std::cout << "输入干扰机" << i << "的参数：" << std::endl;
		ecms[i].read();
	}
	std::cout << "输入敌方雷达数量Nradar：";
	std::cin >> n_radar;
	for (int i = 0; i < n_radar; i++)
	{
		std::cout << "输入雷达" << i << "的参数：" << std::endl;
		radars[i].read();
		radars[i].getR();
		//std::cout << radars[i].R / 1000 << std::endl;
		center = center + radars[i].x;
	}
	center = center / (double)n_radar;
	DE<_ATTR> de(500, 30, tf);
	auto res = de.solve(generator).get_best_agent();
	/*for (int i = 0; i < _ATTR; i++)
		std::cout << res[i] << " ";
	std::cout << std::endl;*/
	for (int i = 0; i < n_ecm; i++)
	{
		std::cout << "第" << i + 1 << "架干扰机的位置为：(" <<
			res[i * 3] / 1000 << "km, " <<
			res[i * 3 + 1] / 1000 << "km, " <<
			res[i * 3 + 2] / 1000 << "km)" << std::endl;
	}
	return 0;
}
