#include "Radar.h"
#include "Global.h"
#include <cmath>
#include <iostream>

void Radar::read()
{
	std::cout << "\t��������x y z��";
	std::cin >> x[0] >> x[1] >> x[2];
	std::cout << "\t���뷢���ֵ����Pt��";
	std::cin >> P;
	std::cout << "\t������������G";
	std::cin >> G;
	std::cout << "\t������ŷ�������G��";
	std::cin >> Gphi;
	std::cout << "\t�����״������ң�";
	std::cin >> sigma;
	std::cout << "\t���벨���ˣ�";
	std::cin >> lambda;
	std::cout << "\t����ϵͳ���L��";
	std::cin >> L;
	std::cout << "\t��������ϵ��Fn��";
	std::cin >> Fn;
	std::cout << "\t���빤���¶�T��";
	std::cin >> T;
	std::cout << "\t������������Bn��";
	std::cin >> Bn;
	std::cout << "\t������Сѹ��ϵ��K��";
	std::cin >> K;
	std::cout << "\t������ջ��źŴ���Br��";
	std::cin >> Br;
	std::cout << "\t���������S/N��";
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
