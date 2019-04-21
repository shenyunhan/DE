#pragma once
#include "Point.h"

struct Radar
{
	Point<> x; // 坐标
	double P; // 发射峰值功率
	double G; // 天线增益
	double sigma; // 截面积
	double lambda; // 波长
	double L; // 系统损耗
	double Fn; // 噪声系数
	double T; // 工作温度
	double Bn; // 噪声带宽
	double Br; // 接收机信号带宽
	double SN; // 信噪比
	double R; // 探测范围
	double K; // 最小压制系数

	void read();
	void getR();
	double getR(double sum);
};