#include "Radar.h"
#include "Global.h"
#include <cmath>
#include <iostream>

void Radar::read()
{
	std::cout << "\t输入坐标x y z：";
	std::cin >> x[0] >> x[1] >> x[2];
	std::cout << "\t输入发射峰值功率Pt：";
	std::cin >> P;
	std::cout << "\t输入天线增益G";
	std::cin >> G;
	std::cout << "\t输入干扰方向增益Gφ";
	std::cin >> Gphi;
	std::cout << "\t输入雷达截面积σ：";
	std::cin >> sigma;
	std::cout << "\t输入波长λ：";
	std::cin >> lambda;
	std::cout << "\t输入系统损耗L：";
	std::cin >> L;
	std::cout << "\t输入噪声系数Fn：";
	std::cin >> Fn;
	std::cout << "\t输入工作温度T：";
	std::cin >> T;
	std::cout << "\t输入噪声带宽Bn：";
	std::cin >> Bn;
	std::cout << "\t输入最小压制系数K：";
	std::cin >> K;
	std::cout << "\t输入接收机信号带宽Br：";
	std::cin >> Br;
	std::cout << "\t输入信噪比S/N：";
	std::cin >> SN;
}

void Radar::getR()
{
	R = pow((P * sqr(G) * sigma * sqr(lambda)) /
		(cub(4 * PI) * SN * Fn * KB * T * Bn * L), 0.25);
}

double Radar::getR(double sum)
{
	return pow((P * sqr(G) * sigma * sqr(lambda)) /
		(cub(4 * PI) * L * Fn * KB * T * Bn * K + sum), 0.25);
}
