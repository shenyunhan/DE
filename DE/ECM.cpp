#include "ECM.h"
#include "Global.h"
#include <iostream>

void ECM::read()
{
	std::cout << "\t输入发射峰值功率Pt：";
	std::cin >> P;
	std::cout << "\t输入天线增益G：";
	std::cin >> G;
	std::cout << "\t输入计划损失r：";
	std::cin >> r;
	std::cout << "\t输入干扰信号带宽B：";
	std::cin >> B;
	std::cout << "\t输入信号综合损耗L：";
	std::cin >> L;
}

double ECM::getR(double phi)
{
	return (4 * PI * P * G * r/* * G(phi)*/) / (cub(B) * L);
}
