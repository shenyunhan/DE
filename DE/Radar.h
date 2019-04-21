#pragma once
#include "Point.h"

struct Radar
{
	Point<> x; // ����
	double P; // �����ֵ����
	double G; // ��������
	double sigma; // �����
	double lambda; // ����
	double L; // ϵͳ���
	double Fn; // ����ϵ��
	double T; // �����¶�
	double Bn; // ��������
	double Br; // ���ջ��źŴ���
	double SN; // �����
	double R; // ̽�ⷶΧ
	double K; // ��Сѹ��ϵ��

	void read();
	void getR();
	double getR(double sum);
};