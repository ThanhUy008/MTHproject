#include "BigCell.h"
#include "Equation.h"
#include "Vector.h"
#include "Matrix.h"
#include <fstream>
string VERSON = "0.0.1";
void booleanHandle()
{

	BigCell holdFirstInput, holdTheBinaryValue, primeImplicant, holdAllTheBigCell;
	vector<BigCell> alternative;
	cout << "Enter the number of variable -> Press Enter then enter the expression" << endl;
	cin >> holdFirstInput;
	holdTheBinaryValue.handleInput(holdFirstInput);

	holdAllTheBigCell = holdTheBinaryValue.allTheBigCell();

	alternative = holdAllTheBigCell.booleanMinimizer(holdTheBinaryValue, primeImplicant);

	if (alternative.size() != 0)
	{
		cout << "The miniminzers are : " << endl;

		for (int i = 0; i < alternative.size(); i++)
		{
			cout << primeImplicant;
			if(!primeImplicant.empty())
				cout << " + ";
			cout << alternative[i] << endl;
		}
	}
	else
	{
		if (!primeImplicant.empty())
		{
			cout << "The miniminzer is : " << endl;
			cout << primeImplicant << endl;
		}
	}
}
int vectorCommand(string in)
{
	if (strcmp(in.c_str(), "add") == 0)
		return 1;
	if (strcmp(in.c_str(), "mul") == 0)
		return 2;
	if (strcmp(in.c_str(), "help") == 0)
		return 4;
	if (strcmp(in.c_str(), "stop") == 0)
		return 5;
	return -1;
}
void vectorHandle()
{
	while (1)
	{
		Vector a, b, c;
		cout << "What you want to do ? " << endl;
		cout << "Adding two vector type add" << endl;
		cout << "Multiply vector with a number type mul" << endl;
		string command;
		getline(cin >> ws, command);
		int choose = vectorCommand(command);
		switch (choose)
		{
		case 1:
			cout << "1. Add two vector: " << endl;
			a.Input();
			b.Input();
			if (a.Check(b) == 1)
			{
				(a + b).Output();
			}
			else cout << "Wrong dimention." << endl;
			break;
		case 2:
			cout << "2. Multiply a vector with a number: " << endl;
			c.Input();
			double alpha;
			cout << "alpha = ";
			cin >> alpha;
			(alpha*c).Output();
			break;
		case 4:
			cout << "Type stop to stop using vector math." << endl;
			break;
		case 5:
			return;
			break;
		case -1:
			cout << "Wrong command." << endl;
			vectorHandle();
			break;
		}
	}
}
int matrixCommand(string in)
{
	if (strcmp(in.c_str(), "det") == 0)
		return 1;
	if (strcmp(in.c_str(), "reci") == 0)
		return 2;
	if (strcmp(in.c_str(), "cal") == 0)
		return 3;
	if (strcmp(in.c_str(), "rank") == 0)
		return 4;
	if (strcmp(in.c_str(), "help") == 0)
		return 5;
	if (strcmp(in.c_str(), "stop") == 0)
		return 6;
	return -1;
}
void matrixHelp()
{
	ifstream inFile;
	inFile.open("m_help.txt");
	if (inFile.fail())
	{
		cout << "There isnt any m_help.txt in your computer" << endl;
		return;
	}
	else
	{
		string output;
		while (getline(inFile, output))
		{
			cout << output << endl;
		}
		inFile.close();
	}
}
void matrixHandle()
{
	Matrix m1, m2, m3, m4, m5;
	while (1)
	{
		cout << "Type help to see option." << endl;
		cout << endl;
		string command;
		getline(cin >> ws, command);
		int choose = matrixCommand(command);
		switch (choose)
		{
		case 1:
			m1.Input();
			m1.Output();
			cout << "Det(A) is : " << m1.Det() << endl;
			break;
		case 2:
			m2.Input();
			m2.Output();
			cout << " Reciprocal matrix : " << endl;
			m2.Inverse().Output();
			break;
		case 3:
			m3.Input();
			m3.Output();
			m4.Input();
			m4.Output();
			m3.Multiply(m4).Output();
			break;
		case 4:
			m5.Input();
			m5.Output();
			cout << "Rank(A): " << m5.Rank() << endl;
			break;
		case 5:
			matrixHelp();
			break;
		case 6:
			return;
			break;
		case -1:
			cout << "Wrong command." << endl;
			matrixHandle();
			break;
		}
	}
}
void equationsHandle()
{
	Equations A;
	cout << "Linear equation : " << endl;
	cout << endl;
	if (A.InputEquations())
	{
		A.OutputEquations();
		A.Solution();
	}
	else
	{
		return;
	}

}
void menu()
{
	cout << "      WELCOME AND THANK YOU FOR USING OUR TOOL                      |" << endl;
	cout << "        ______        ______    ____________       ___       ___    |M.T.H VER " <<VERSON<<  endl;
	cout << "       /      |      /  |   |  |____    ____|     |   |     |   |   |Type help to see the help." << endl;
	cout << "      /       |     /   |   |       |   |         |   |     |   |   |" << endl;
	cout << "     /    /|  |    /   /|   |       |   |         |   |_____|   |   |" << endl;
	cout << "    /    / |  |   /   / |   |       |   |         |   ______    |   |" << endl;
	cout << "   /    /  |  |  /   /  |   | ____  |   |   ____  |   |     |   |   |" << endl;
	cout << "  /____/   |____/___/   |___| |__|  |___|   |__|  |___|     |___|   |Type stop to stop the program." << endl;

}
void Help()
{
	ifstream inFile;
	inFile.open("help.txt");
	if (inFile.fail())
	{
		cout << "There isnt any help.txt in your computer" << endl;
		return;
	}
	else
	{
		string output;
		while (getline(inFile, output))
		{
			cout << output << endl;
		}	
		inFile.close();
	}
}
int checkCommand(string in)
{
	if (strcmp(in.c_str(), "bool") == 0)
		return 1;
	if (strcmp(in.c_str(), "vec") == 0)
		return 2;
	if (strcmp(in.c_str(), "matrix") == 0)
		return 3;
	if (strcmp(in.c_str(), "equation") == 0)
		return 4;
	if (strcmp(in.c_str(), "help") == 0)
		return 5;
	if (strcmp(in.c_str(), "stop") == 0)
		return 6;
	return -1;
}

void main()
{
	menu();
	do 
	{
	
		cout << "Please type your command." << endl;
		string command,getstop;
		getline(cin >> ws, command);
		cout << endl;
		int type_of_mth = checkCommand(command);
		switch (type_of_mth)
		{
		case 1:
			booleanHandle();
			break;
		case 2:
			vectorHandle();
			break;
		case 3:
			matrixHandle();
			break;
		case 4:
			equationsHandle();
			break;
		case 5:
			Help();
			break;
		case 6:
			return;
			break;
		case -1:
			cout << "Wrong command." << endl;

			break;
		}
	}while(1);
}