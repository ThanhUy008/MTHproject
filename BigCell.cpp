#include "BigCell.h"
//kiem tra string dua vao co phai duoi dinh dang 1 so hay khong
bool isCorrect(std::string input)
{
	if (input.size() < 1) return false;
	for (int i = 0; i < input.size(); i++)
	{

		
			if (!(input[i] - 48 < 10 && input[i] - 48 >= 0)) return false;
		
	}

	return true;
}
//chuyen doi string thanh con so tuong ung
int covertStrToInt(std::string input)
{
	float digit = 1;
	for (int i = 0; i < input.size() - 1; i++)
	{
		digit *= 10;
	}
	int temp = 0;
	for (int i = 0 ; i < input.size(); i++)
	{
			temp += (input[i] - '0') * digit;
			digit /= 10;
	}
	return temp;
}
//input contain value if a cell are added with another
//this function is to check is all the value are 0
bool isUnAddable(const vector<int> input)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] != 0)
			return false;
	}
	return true;
}
//copy string in to string des (which is still empty)
void copyVector(vector<string> &des, vector<string> in)
{
	for (int i = 0; i < in.size(); i++)
	{
		des.push_back(in[i]);
	}
}
//remove value out of vector<int>
void flushFlag(vector<int> &input)
{
	while (!input.empty())
		input.pop_back();
}
//check is value i is in vector<int>
bool isIn(vector<int> input, int i)
{
	for (int k = 0; k < input.size(); k++)
	{
		if (i == input[k]) return true;
	}
	return false;
}
BigCell::BigCell()
{
	_n = 0;
}

BigCell::BigCell(const BigCell & b)
{
	_n = b._n;
	_big = b._big;
}
void BigCell::defineType(int type)
{
	_n = type;
	for (int i = 0; i < _big.size(); i++)
	{
		_big[i].getType() = _n;
	}
}
//check if Cell b are in Bigcell yet, if not , add Cell b to Bigcell
void BigCell::check(Cell b)
{
	for (int i = 0; i < _big.size(); i++)
	{
		if (_big[i]== b)
		{
			return;
		}
	}
	b.setType(_n);
	_big.push_back(b);
}
//convert cell like 1--0 to 1000,1100,1110,.. then add it in Bigcell
void BigCell::turnOn(Cell b)
{
	//check if there are any "-" left.
	//if not then add the binary value of cell to bigcell
	int count = b.n_ignore();
	if (count == 0)
	{
		this->check(b);
	}
	else
	{
		//if there still "-" value, change it to '0' and '1' accordingly to get all the small cell
		for (int i = 1; i <= count; i++)
		{
			int k = b.findIgnore(i);
			if (k != -1)
			{
				b[k] = '0';
				turnOn(b);
				b[k] = '1';
				turnOn(b);
			}
		}
	}
}
//turn Cell b from "abc" to "111" then find the others possibility
void BigCell::handleOneInput(Cell b)
{
	Cell temp("");
	_n = b.getType();
	for (int i = 0; i < _n; i++)
	{
		temp = temp + '-';
	}
	//convert cell value to binary value
	for (int i = 0; i < b.size(); i++)
	{
		int j = 0;
		while (j < _n)
		{
			if (b[i] - 'a' == j)
			{
				if (b[i + 1] - ' ' == 7)
					temp[j] = '0';
				else temp[j] = '1';
				break;
			}
			j++;
		}
	}
	
	this->turnOn(temp);

}
//Handle all the input
void BigCell::handleInput(BigCell b)
{
	//convert all the input cell to binary value
	for (int i = 0; i < b._big.size(); i++)
	{
		this->handleOneInput(b._big[i]);
	}
	this->defineType(b._n);

}
//remove Cell[i] out of Bigcell
void BigCell::pop(int i)
{
	if (_big.size() > 0)
	{
		//check if bigcell have only one value or i-th value is the last value of the vector.
		//if true, remove it easily.
		if (_big.size() == 1 || i == _big.size() - 1)
		{
			_big.pop_back();
		}
		else
		{
			for (int k = i; k < _big.size()-1; k++)
			{
				_big[k] = _big[k+1];
			}
			_big.pop_back();
		}
	}
}
//sort the Bigcell according to the number of 1 it contain
//required by the algorithm
void BigCell::sortBy1()
{
	for (int i = 0; i < _big.size(); i++)
	{
		for (int j = i + 1; j < _big.size(); j++)
		{
			int a = _big[i].n_1();
			int b = _big[j].n_1();
			if (a > b)
			{
				Cell temp(_big[i]);
				_big[i] = _big[j];
				_big[j] = temp;
			}
		}
	}
}
//after a round of adding, we remove mark to now all the new cells are not add with any other cell
void BigCell::removeAllMark()
{
	for (int i = 0; i < _big.size(); i++)
	{
		_big[i].removeMark();
	}
}

//copy from cell b
void BigCell::copyCell(const BigCell &b)
{
	//add bigcell b to this->bigcell
	_n = b._n;
	for (int i = 0; i < b._big.size(); i++)
	{
		_big.push_back(b._big[i]);
	}
}
//if Bigcell are contain a cell which is smaller and can be replace by another bigcell in the vector remove it
BigCell BigCell::removeSmaller()
{
	
	for (int i = 0; i < _big.size(); i++)
	{
		for (int j = 0; j < _big.size(); j++)
		{
			if (i != j)
			{
				if (_big[i].isContain(_big[j]))
				{
					this->pop(j);
					break;
				}
			}
		}
	}
	return *this;
}

//find the prime cell
//return the the bigcell which isnt the prime implicants.
//output is contain the value of prime implicants
BigCell BigCell::findThePrimeCell(BigCell & smallcell,BigCell &output)
{
	vector<int> biggestCell;

	BigCell leftOver;

	leftOver._n = _n;
	
	BigCell input(*this);
	
	output._n = _n;
	//loop until cant not find any prime impilicants
	do
	{
		input.sortMotherCell(smallcell);
		flushFlag(biggestCell);

		leftOver.~BigCell();
		//lap bang tim Prime Cell

		vector<int> uselessrow;
		vector<int> count;
		//count will be seen as a 2D-matrix

		for (int i = 0; i < input._big.size(); i++)
		{
			for (int j = 0; j < smallcell._big.size(); j++)
			{
				int temp = 0;
				if (input._big[i].isContain(smallcell._big[j]))
				{
					temp = 1;
				}
				count.push_back(temp);
			}
		}

		int MaxCol = smallcell._big.size();

		for (int i = 0; i < input._big.size(); i++)
		{
			int flag = 0;
			for (int j = 0; j < smallcell._big.size(); j++)
			{
				if (count[i * MaxCol + j] == 1) flag++;
			}
			if (flag == 0)
			{
				uselessrow.push_back(i);
			}
		}
		
		//find the prime implicants by finding the the col with only 1 value "1"
		for (int j = 0; j < smallcell._big.size(); j++)
		{
			//flag is to save the number of 1 value of the collum.
			//save is saving the value of row have a collum with only one value "1".
			int flag = 0, save = -1;
			for (int i = 0; i < input._big.size(); i++)
			{

				if (count[i * MaxCol + j] == 1)
				{
					//if the value of the the count[i,j] = 1, increase the flag. 
					flag++;
					//saving the value the the last row which collum have "1" value.
					save = i;
				}
			}
			if (flag == 1)
			{
				//if the collum have only one value "1", add the bigcell of the according row to output.
				output.check(input._big[save]);
				//save the value of the row to remove it out the table later.
				biggestCell.push_back(save);
			}
		}
		
		//Find what isn't in Prime Cell and get it in leftOver

		for (int i = 0; i < input._big.size(); i++)
		{
			//if the row isnt one of the row which have a collum with only one value "1"
			//add it to the leftover cell
			if (!isIn(biggestCell, i))
			{
				if (!isIn(uselessrow, i))
				{
					leftOver._big.push_back(input._big[i]);
				}
			}
		}

		//Reduce First Small Cell
		int check = 0;
		do {
			//because after POP the position of the smallcell is renew. so we ne do check it again.
			check = 0;
			for (int i = 0; i < smallcell._big.size(); i++)
			{
				for (int j = 0; j < output._big.size(); j++)
				{
					//if the small cell is contain in the prime implicants then pop it out
					if (output._big[j].isContain(smallcell._big[i]))
					{
						
						smallcell.pop(i);
						check = 1;
						break;
					}
				}
			}
		} while (check != 0);

		flushFlag(count);

		//remove the input which contain all the bigcell and replace it which leftover to continue finding the prime cell.
		input.~BigCell();
	
		input.copyCell(leftOver);

		//if there aren't anymore prime implicants break the loop;
	} while (!biggestCell.empty());
	//have all the smallcell in leftOver _type = _n;
	leftOver.defineType(this->_n);
	//return the leftover which is not the prime implicants
	return leftOver;
}
//check if the bigcell are cover all the small cell
bool BigCell::isFullyCover(BigCell smallCell)
{
	vector<int> flag;
	//init the flag with all 0
	for (int j = 0; j < smallCell._big.size(); j++)
	{
		flag.push_back(0);
	}
	for (int i = 0; i < _big.size(); i++)
	{
		for (int j = 0; j < smallCell._big.size(); j++)
		{
			//if bigcell contain small cell then giving flag[i] value one.
			if (_big[i].isContain(smallCell._big[j]))
			{
				flag[j] = 1;
			}
		}
	}
	//if all the flag value is 1 then the big cell is completely cover the small cell.
	for (int j = 0; j < smallCell._big.size(); j++)
	{
		if (flag[j] != 1)
			return false;
	}
	return true;
}
//after get prime cell, we need to remove it and the small cell it contain to keep rolling the algorithm
void BigCell::removeBigAndSmallCells(BigCell & small, int k)
{

	if (_big.size() > 0)
	{
		Cell temp(_big[k]);
		while (k >= 0)
		{
			this->pop(0);
			k--;
		}
		//Reduce First Small Cell
		int check;
		do {
			check = 0;
			for (int i = 0; i < small._big.size(); i++)
			{
				if (temp.isContain(small._big[i]))
				{
					small.pop(i);
					check = 1;
					break;
				}
			}
		} while (check != 0);

	}
}
//if after all the prime cell are find and still cant cover all the small cell, we find the replacement.
//alternative is to saving all the bigcell can cover the rest of the small cell
//temp1 is to save the bigcell can cover the small cell. if it is cover then push in the alternative.
void BigCell::findAlternative(BigCell SmallerCell, BigCell & temp1, vector<BigCell> &alternative)
{
	for (int i = 0; i < _big.size(); i++)
	{

		BigCell leftOver;

		BigCell saveSmallCells(SmallerCell);

		BigCell savebigCells(*this);

		temp1._n = this->_n;
		//get a bigcell to the temp1, because cant find the prime implicants anymore so we consider the i-th row is a prime implicants.

		temp1._big.push_back(savebigCells._big[i]);
		//check if the temp is cover all the small cell or not.
		// if true then add the temp1 to the alternative.
		//pop the newly add cell(from the bigcell) from temp1 and add the next cell to temp1.

		if (temp1.isFullyCover(saveSmallCells))
		{
			//priority(alternative, temp1, i);
			alternative.push_back(temp1);
			//	temp1._big.pop_back();

		}
		else
		{
			//if isnt covered all the small then pop remove the big cell and small cell then continue to find prime implicants.
			savebigCells.removeBigAndSmallCells(saveSmallCells, i);
			if (savebigCells._big.size() != 0)
			{

				BigCell tempOutput(temp1);

				leftOver = savebigCells.findThePrimeCell(saveSmallCells, tempOutput);
				//if there still more big cell that isnt prime implicants
				if (tempOutput.isFullyCover(saveSmallCells))
				{
					alternative.push_back(tempOutput);
				}
				else
				{
					leftOver.findAlternative(saveSmallCells, tempOutput, alternative);
				}

			}
		}
		//back track when out of loop
		if (!temp1._big.empty())
			temp1._big.pop_back();

	}
}



//find all the bigcell by adding small cell together and keep doing that until cant .

BigCell BigCell::allTheBigCell()
{
	BigCell temp(*this);

	BigCell output;

	output._n = _n;

	int n = _big.size();
	//sort all the cell by the number of "1" contain
	this->sortBy1();



	vector<int> flag;
	//loop until all the small cell are not addable
	do
	{
		flushFlag(flag);

		//holder is to save all the cell after add.
		BigCell holder;
		holder._n = _n;

		//if there are only one left, add it in holder
		if (temp._big.size()	 == 1)
		{
			holder.check(temp._big[0]);
		}

		else
		{
			//adding two cell together by the algorithm
			for (int i = 0; i < temp._big.size(); i++)
			{
				//dem is to check if the cell is addable or not
				int dem = 0;
				for (int j = i + 1; j < temp._big.size(); j++)
				{
					//because after adding, the cell is changed so we need temp cell
					Cell cong_temp(temp._big[i]);

					if (cong_temp.canAdd(temp._big[j],_n))
					{
						//if can add with cell[j] we add the temp to holder where save
						//all the cells changed after added
						
						dem++;
						holder.check(cong_temp);
						//forgot what this does.
						temp._big[i].removeMark();

						//mark cell[j] because in holder there are already cell contain it.
						temp._big[j].markAferAdd();
					}
				}
				if (dem == 0)
				{
					//if the cell is not addable. check if is added by anyother cell
					if (!temp._big[i].isAdded())
						//if not add it in big cell
						output.check(temp._big[i]);
				}
				
				flag.push_back(dem);
			}
		}
		//if all the cell is unaddable then we finish finding the bigcell
		if (isUnAddable(flag)) break;
		else
		{
			//if not, we remove the mark to know all the new cell is not added
			holder.removeAllMark();
			temp.~BigCell();
			//copy the holder to temp to continue looping.
			temp.copyCell(holder);
			//empty holder for saving new added cell
			holder.~BigCell();
		}

	} while (1);
	//if the loop is over, adding the leftover cell to ouput since they are important cell.
	output.copyCell(temp);
	//this remove all the cell that is contained by the cell already in output.
	//just double check it.
	output = output.removeSmaller();
	
	output.defineType(this->_n);
	return output;
}

//find the minimizers, if there are more than one than return a vector<bigcell>
//if there are only one, return an empty vector<bigcell>.
//output are the essential cell
vector<BigCell> BigCell::booleanMinimizer(BigCell firstSmallCell,BigCell &output)
{


	BigCell leftOver;
	leftOver._n = _n;

	BigCell n_output;

	n_output._n = _n;

	vector<BigCell> lastel;

	//find the prime cell
	leftOver = this->findThePrimeCell(firstSmallCell, output);
	
	output.covertOutput();
	//if there are still big cell that are not prime implicants we find the replacements for it.
	if (leftOver._big.size() != 0)
	{
		leftOver.sortMotherCell(firstSmallCell);
		leftOver.findAlternative(firstSmallCell, n_output, lastel);

		for (int i = 0; i < lastel.size(); i++)
		{
			lastel[i].defineType(_n);
			lastel[i].covertOutput();
			
		}
	}
	return lastel;
}
void BigCell::sortMotherCell(BigCell smallcell)
{
	BigCell input(*this);

	//loop until cant not find any prime impilicants
		//lap bang tim Prime Cell

		vector<int> row;
		vector<int> count;
		//count will be seen as a 2D-matrix

		for (int i = 0; i < input._big.size(); i++)
		{
			for (int j = 0; j < smallcell._big.size(); j++)
			{
				int temp = 0;
				if (input._big[i].isContain(smallcell._big[j]))
				{
					temp = 1;
				}
				count.push_back(temp);
			}
		}

		int MaxCol = smallcell._big.size();


		for (int i = 0; i < input._big.size(); i++)
		{
			int flag = 0;
			for (int j = 0; j < smallcell._big.size(); j++)
			{
				if (count[i * MaxCol + j] == 1) flag++;
			}
			row.push_back(flag);
		}
	
		for (int i = 0; i < row.size(); i++)
		{

			for (int j = i + 1; j < row.size(); j++)
			{
				if (row[i] < row[j])
				{
					swap(row[i], row[j]);
					Cell temp;
					temp = _big[i];
					_big[i] = _big[j];
					_big[j] = temp;
				}
			}
		}
		row;
		int k = 0;

}

//check if two bigcell is the same or not


//conver big cell from binary value to string value
void BigCell::covertOutput()
{
	for (int i = 0; i < _big.size(); i++)
	{
		_big[i].convert();
	}
	
}

BigCell & BigCell::operator=(const BigCell & b)
{
	_big = b._big;
	_n = b._n;
	return *this;
}

bool BigCell::empty()
{
	if (_big.empty()) return true;
	return false;
}


BigCell::~BigCell()
{
	while (!_big.empty())
	{
		_big.pop_back();
	}
}

istream & operator >> (istream & in, BigCell & b)
{
	string type_var;
	getline(cin >> ws, type_var);
	if (isCorrect(type_var))
	{
		b._n = covertStrToInt(type_var);
	}
	else
	{
		cout << "Wrong input" << endl;
		return in;
	}
	//string ignore_out;
	//getline(in, ignore_out);
	Cell temp;
	char trash,c;
	while (!in.eof())
	{
		if (in.peek() == ' ')
		{
			in.ignore();
		}
		else if (in.peek() == '\n' || in.peek() == -1)
		{
			b._big.push_back(temp);
			break;
		}
		else if (in.peek() == '+')
		{
			if (!temp.isEmpty())
				b._big.push_back(temp);
			temp.~Cell();
			in.ignore();
		}
		else
		{
			c = in.get();
			trash = in.peek();
			temp.pushback(c);
		}
	}
	b.defineType(b._n);
	return in;
}

ostream & operator<<(ostream & out, const BigCell & b)
{
	for (int i = 0; i < b._big.size(); i++)
	{
		out << b._big[i];
		if (i != b._big.size() - 1)
			out << " + ";
	}
	return out;
}
