#include "Radar.h"
#include "Global.h"
#include <cmath>
#include <iostream>

void Radar::read()
{
	//std::cout << "\t��������x y z��";
	std::cin >> x[0] >> x[1] >> x[2];
	//std::cout << "\t���뷢���ֵ����Pt/kW��";
	std::cin >> P;
	//std::cout << "\t������������G��";
	std::cin >> G;
	//std::cout << "\t������ŷ�������G�գ�";
	std::cin >> Gphi;
	//std::cout << "\t�����״�������/m^2��";
	std::cin >> sigma;
	//std::cout << "\t���벨����/m��";
	std::cin >> lambda;
	//std::cout << "\t����ϵͳ���L��";
	std::cin >> L;
	//std::cout << "\t��������ϵ��Fn��";
	std::cin >> Fn;
	//std::cout << "\t���빤���¶�T/K��";
	std::cin >> T;
	//std::cout << "\t������������Bn/kHz��";
	std::cin >> Bn;
	//std::cout << "\t������ջ��źŴ���Br/kHz��";
	std::cin >> Br;
	//std::cout << "\t���������S/N��";
	std::cin >> SN;
	//std::cout << "\t������Сѹ��ϵ��K��";
	std::cin >> K;
	x = x * 1000.0;
	P *= 1000;
	Bn *= 1000, Br *= 1000;
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
