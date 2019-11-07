#include "Matrix.h"

Matrix::Matrix()//Ham khoi tao khong truyen tham so
{
	_row = _colum = 0;//Mac dinh dong va cot bang 0
	_m = NULL;//Ma tran rong
}
Matrix::~Matrix()//Ham huy
{
	if (_m == NULL) return;//neu ma tran rong thi khong thuc hien
	for (int i = 0; i < _row; i++)
	{
		delete[]_m[i];//Giai phong vung nho cho tung dong trong ma tran
		_m[i] = NULL;
	}
	delete[]_m;//Giai phong vung nho cho ca ma tran
	_m = NULL;
}
Matrix::Matrix(int _r, int _c)//Ham khoi tao co tham so truyen vao
{
	_row = _r;
	_colum = _c;
	_m = new double *[_r];
	for (int i = 0; i < _r; i++)
		_m[i] = new double[_c];
}
Matrix::Matrix(const Matrix &m1)//Ham khoi tao sao chep
{
	_row = m1._row;
	_colum = m1._colum;
	_m = new double*[_row];//Cap phat _row dong
	for (int i = 0; i < _row; i++)
	{
		_m[i] = new double[_colum];//Cap phat _colum cot
		for (int j = 0; j < _colum; j++)
			_m[i][j] = m1._m[i][j];
	}
}
void Matrix::Set_row(int row)//Tao gia tri moi cho _row
{
	_row = row;
}
void Matrix::Set_colum(int colum)//Tao gia tri moi cho _colum
{
	_colum = colum;
}
void Matrix::Input()//Phuong thuc nhap
{
	cout << "Enter row and col value : " << endl;
	cin >> _row >> _colum;
	cout << "Enter matrix value: " << endl;
	_m = new double *[_row];//Cap phat dong
	for (int i = 0; i < _row; i++)
		_m[i] = new double[_colum];//Cap phat cot
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _colum; j++)
		{
			cout << "m[" << i << "][" << j << "]: ";
			cin >> _m[i][j];
		}
	}
}
int Matrix::Get_row()//Lay gia tri cua _row
{
	return _row;
}
int Matrix::Get_colum()//Lay gia tri cua _colum
{
	return _colum;
}
double** Matrix::Get_m()//Lay gia tri ma tran
{
	return _m;
}
void Matrix::Output()//Phuong thuc xuat
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _colum; j++)
		{
			cout << setw(6) << setprecision(3) << _m[i][j] << " ";
		}
		cout << endl;
	}
}
Matrix& Matrix::operator=(const Matrix m1)//Ham khoi tao sao chep
{
	_row = m1._row;
	_colum = m1._colum;
	_m = new double*[_row];//Cap phat _row dong
	for (int i = 0; i < _row; i++)
		_m[i] = new double[_colum];//Cap phat _colum cot
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _colum; j++)
			_m[i][j] = m1._m[i][j];
	}
	return *this;
}
Matrix Matrix::MatrixExceptRowColum(int _r, int _c)//Ma tran xoa di dong _r va cot _c
{
	Matrix temp(_row - 1, _colum - 1);

	int m = -1;
	int n;
	for (int i = 0; i < _row; i++)
	{
		if (i != _r)
			m++;
		n = -1;
		for (int j = 0; j < _colum; j++)
		{
			if (j != _c)
				n++;
			if (i != _r && j != _c)
				temp._m[m][n] = _m[i][j];

		}
	}
	return temp;
}
double Matrix::Det()//Tinh dinh thuc
{
	if (_row != _colum)
	{
		cout << "Matrix isn't square matrix." << endl;
		return NULL;
	}
	else
	{
		double det = 0;
		if (_row == 1)
			return _m[0][0];
		else
		{
			for (int i = 0; i < _row; i++)
			{
				det += pow(-1, i)*_m[0][i] * MatrixExceptRowColum(0, i).Det();
			}
			return det;
		}
	}
}
Matrix Matrix::Inverse()//Tim ma tran nghich dao
{
	if (_row != _colum)
	{
		cout << "Reciprocal matrix doenst exist." << endl;
		return Matrix();
	}
	if (Det() == 0)
	{
		cout << "Reciprocal matrix doenst exist." << endl;
		return Matrix();
	}
	else
	{
		Matrix inverse(_row, _colum);
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _colum; j++)
			{
				inverse._m[i][j] = (pow(-1, i + j)*MatrixExceptRowColum(j, i).Det()) / Det();
			}
		}
		return inverse;
	}
}
Matrix Matrix::Multiply(Matrix m1)//Tich hai ma tran
{
	if (_colum != m1._row) {
		cout << "Can't multiply these two matrix." << endl;
		return Matrix();
	}
	else {
		Matrix mul(_row, m1._colum);
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < m1._colum; j++)
			{
				mul._m[i][j] = 0;
				for (int k = 0; k < _colum; k++)
					mul._m[i][j] += _m[i][k] * m1._m[k][j];
			}

		}
		return mul;
	}

}
int Matrix::Rank()//Tim hang
{
	//Dua ma tran ve ma tran bac thang
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _colum; j++)
		{
			if (_m[i][j] += 0)
			{
				for (int k = i + 1; k < _row; k++)
				{
					if (_m[k][j] != 0)
					{
						for (int u = 0; u < _colum; u++)
						{
							swap(_m[i][u], _m[k][u]);
							/*float temp = _m[i][u];
							_m[i][u] = _m[k][u];
							_m[k][u] = temp;*/
						}
						break;
					}
				}
			}
			if (_m[i][j] != 0)
			{
				for (int k = i + 1; k < _row; k++)
				{
					double tiLe = (double)_m[k][j] / _m[i][j];
					for (int u = 0; u < _colum; u++)
						_m[k][u] -= _m[i][u] * tiLe;
				}
				break;
			}
		}
	}
	int rank = 0;
	for (int i = _row - 1; i >= 0; i--)//Cho chay tu dong cuoi len tren
	{
		for (int j = 0; j < _colum; j++)//Cho chay tu cot dau tien den cot cuoi cung
		{
			if (_m[i][j] != 0)//Gia tri 
			{
				rank++;
				break;//Vong lap bi ket thuc khong tang j, tiep tuc tang i
			}
		}
	}
	return rank;
}





