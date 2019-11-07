#pragma once
#include<iostream>
using namespace std;

class Vector
{
private:
	int _n;
	double *_v;
public:
	Vector();//Ham tao khong co tham so truyen vao
	~Vector();//Ham huy
	Vector(int size);//Ham tao co tham so truyen vao
	Vector(Vector &a);//Ham tao sao chep
	Vector& operator =(Vector a);//Toan tu gan
	void Input();//Phuong thuc nhap
	void Output();//Phuong thuc xuat
	int Check(Vector &a);//Kiem tra 2 vector co do dai bang nhau khong
	friend Vector operator +(Vector &a, Vector &b);//Toan tu cong
	friend Vector operator *(const double &alpha, Vector &a);//Toan tu nhan
};


