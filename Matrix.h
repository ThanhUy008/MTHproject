#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

class Matrix
{
public:
	int _row;//so hang
	int _colum;//So cot
	double **_m;//Ma tran
public:
	Matrix();//Ham khoi tao khong truyen tham so
	~Matrix();//Ham huy
	Matrix(int _row, int _colum);//Ham khoi tao co tham so truyen vao
	Matrix(const Matrix &m1);//Ham khoi tao sao chep
	Matrix& operator=(const Matrix m1);//Toan tu gan
	void Set_row(int row);//Tao gia tri moi cho _row
	void Set_colum(int colum);//Tao gia tri moi cho _colum
	void Input();//Phuong thuc nhap
	int Get_row();//Lay gia tri cua _row
	int Get_colum();//Lay gia tri cua _colum
	double **Get_m();//Lay gia tri ma tran
	void Output();//Phuong thuc xuat
	Matrix MatrixExceptRowColum(int _r, int _c);//Ma tran xoa di dong _r va cot _c
	double Det();//Tinh dinh thuc
	Matrix Inverse();//Tim ma tran nghich dao
	Matrix Multiply(Matrix m1);//Tich hai ma tran
	Matrix operator*(Matrix m1);//Toan tu nhan
	int Rank();//Tim hang 
};