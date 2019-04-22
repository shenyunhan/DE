#pragma once

struct ECM
{
	double P; // 发射功率
	double G; // 天线增益
	double r; // 极化损失
	double B; // 干扰信号带宽
	double L; // 信号综合损耗

	void read();
	double getR();
};
