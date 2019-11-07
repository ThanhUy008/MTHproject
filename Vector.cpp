#include "Vector.h"

Vector::Vector()//Ham khoi tao
{
	_v = NULL;
}
Vector::~Vector()//Ham huy
{
	if (_v != NULL)
		delete[] _v;
}
Vector::Vector(int size)//Ham tao co tham so truyen vao
{
	_n = size;
	_v = new double[_n];
}
Vector::Vector(Vector &a)//Ham tao sao chep
{
	_n = a._n;
	_v = new double[_n];
	for (int i = 0; i<_n; i++)
		_v[i] = a._v[i];
}
void Vector::Input()//Phuong thuc nhap
{
	cout << "Enter vector dimention : "; cin >> _n;
	cout << "Enter vector value: " << endl;
	_v = new double[_n];
	for (int i = 0; i<_n; i++)
	{
		cout << " v[" << i << "]: ";
		cin >> _v[i];
	}
}
void Vector::Output()//Phuong thuc xuat
{
	cout << "Vector : ";
	cout << "(";
	for (int i = 0; i < _n; i++)
	{
		cout << " " << _v[i] << " ";
	}
	cout << ")" << endl;;
}
Vector& Vector:: operator =(Vector a)//Toan tu gan
{
	_n = a._n;
	_v = new double[_n];
	for (int i = 0; i < _n; i++)
		_v[i] = a._v[i];
	return *this;
}
Vector operator +(Vector &a, Vector &b)//Cong hai vector
{
	Vector c = a;
	for (int i = 0; i<a._n; i++)
		c._v[i] = a._v[i] + b._v[i];
	return c;
}
int Vector::Check(Vector &b)//Kiem tra do dai hai vector co bang nhau hay khong
{
	if (_n == b._n)
		return 1;
	return 0;
}
Vector operator *(const double &alpha, Vector &a)//Nhan vector voi mot so alpha
{
	Vector d = a;
	for (int i = 0; i < a._n; i++)
		d._v[i] = alpha * a._v[i];
	return d;
}
