#include "ECM.h"
#include "Global.h"
#include <iostream>

void ECM::read()
{
	std::cout << "\t���뷢���ֵ����Pt��";
	std::cin >> P;
	std::cout << "\t������������G��";
	std::cin >> G;
	std::cout << "\t����ƻ���ʧr��";
	std::cin >> r;
	std::cout << "\t��������źŴ���B��";
	std::cin >> B;
	std::cout << "\t�����ź��ۺ����L��";
	std::cin >> L;
}

double ECM::getR(double phi)
{
	return (4 * PI * P * G * r/* * G(phi)*/) / (cub(B) * L);
}
