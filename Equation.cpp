#include "Equation.h"
#include "Matrix.h"

Equations::Equations()//Khong co thanh phan dong nen chi de rong
{
}

Equations::~Equations()//Khong co thanh phan dong nen chi de rong
{
}
bool Equations::InputEquations()//Ham nhap he phuong trinh
{
	
		cout << "Enter Factor Matrix: " << endl;
		Factor.Input();
		cout << "Enter Free Factor Matrix: " << endl;
		FreeFactor.Input();
		if (FreeFactor.Get_colum() != 1 || Factor.Get_row() != FreeFactor.Get_row())
		{
			cout << "Wrong input." << endl;
			return false;
		}
		return true;
		
}
void Equations::OutputEquations()//Ham xuat he phuong trinh
{
	double **_Factor = Factor.Get_m();
	double **_FreeFactor = FreeFactor.Get_m();
	cout << "Linear equations: " << endl;
	for (int i = 0; i < Factor.Get_row(); i++)
	{
		for (int j = 0; j < Factor.Get_colum(); j++)
		{
			cout << setw(6) << setprecision(3) << _Factor[i][j] << " ";
		}
		cout << " |" << setw(6) << setprecision(3) << _FreeFactor[i][0] << " ";
		cout << endl;
	}
}

void Equations::Solution()//Ham giai hpt tuyen tinh
{
	Matrix MoreFactor(Factor.Get_row(), Factor.Get_colum() + 1);// Tao ma tran he so mo rong co dong bang dong cua ma tran he so va cot bang cot ma tran he so cong 1
	for (int i = 0; i < Factor.Get_row(); i++)
	{
		for (int j = 0; j < Factor.Get_colum() + 1; j++)
		{
			MoreFactor._m[i][j] = Factor._m[i][j];//Lay gia tri cua ma tran he so 
		}
		MoreFactor._m[i][Factor.Get_colum()] = FreeFactor._m[i][0];//Lay gia tri cua ma tran he so tu do
	}
	cout << "Open Factor Matrix: " << endl;
	MoreFactor.Output();
	if (Factor._row < Factor._colum)//So phuong trinh nho hon so an
	{
		cout << "There are inf root." << endl;
	}
	else if (Factor._row >Factor._colum)//So phuong trinh nhieu hon so an
	{
		cout << "There arent any root." << endl;
	}
	else //So phuong trinh bang so an
	{
		int r1 = Factor.Rank();//Hang cua ma tran he so tu do
		int r2 = MoreFactor.Rank();//Hang cua ma tran he so mo rong
		if (r1 < r2)
			cout << "There arent any root." << endl;
		else if (r1 == r2)
		{
			if (r1 < Factor._row)//Hang cua ma tran he so tu do nho hon so an
				cout << "There are inf root." << endl;
			else
			{
				cout << "The only root is : " << endl;
				MoreFactor = Factor.Inverse().Multiply(MoreFactor);//Ma tran nghich dao cua ma tran he so tu do nhan voi ma tran he so mo rong
																   //Vi du doi voi hpt 3 an 3 PT, ma tran tren co dang:
																   // 1  0  0  x1
																   // 0  1  0  x2
																   // 0  0  1  x3
																   //Nghiem la gia tri cot thu (_colum - 1) cua ma tran tren
				for (int i = 0; i < MoreFactor._row; i++)
				{
					cout << "Root " << i + 1 << ": " << MoreFactor._m[i][MoreFactor._colum - 1] << endl;
				}
			}
		}
	}
}
