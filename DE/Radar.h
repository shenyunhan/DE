#pragma once
#include "Point.h"

struct Radar
{
	Point<> x; // ����
	double P; // �����ֵ����
	double G; // ��������
	double Gphi; // ���ŷ�������
	double sigma; // �����
	double lambda; // ����
	double L; // ϵͳ���
	double Fn; // ����ϵ��
	double T; // �����¶�
	double Bn; // ��������
	double Br; // ���ջ��źŴ���
	double SN; // �����
	double K; // ��Сѹ��ϵ��
	double R; // ̽�ⷶΧ

	void read();
	void getR();
	double getR(double sum);
};