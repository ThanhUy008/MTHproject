#pragma once
#include"Matrix.h"

class Equations
{
private:
	Matrix Factor;//Ma tran he so
	Matrix FreeFactor;//Ma tran he so tu do
public:
	Equations();//Ham khoi tao khong truyen tham so
	~Equations();//Ham huy
	bool InputEquations();//Ham nhap he phuong trinh
	void OutputEquations();//Ham xuat he phuong trinh
	void Solution();//Ham giai hpt tuyen tinh
};

