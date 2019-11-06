#include "Cell.h"



Cell::Cell()
{ 
	_type = 0;
	_isCong = false;
}

Cell::Cell(const string & b)
{
	_c = b;
}

Cell::Cell(const Cell & b)
{
	_type = b._type;
	_c = b._c;
	_isCong = b._isCong;
}

void Cell::pushback(char c)
{
	//use in entering input
	_c.push_back(c);
}

void Cell::markAferAdd()
{
	//use in algorithm.
	//Mark cell to not add the smaller cell when there are already bigcell in it
	_isCong = true;
}

void Cell::removeMark()
{
	//use in algorithm
	_isCong = false;

}






void Cell::setType(int n)
{
	//when add a new cell, chances are it _type will be = 0, this to set the _type
	_type = n;
}

int& Cell::getType()
{
	return _type;
}

int Cell::n_1()
{
	//return the number of 1 in binary value of a cell.
	//use to sort.
	int rel = 0;
	for (int i = 0; i < _c.size(); i++)
	{
		if (_c[i] == '1')
			rel++;
	}
	return rel;
}

int Cell::n_ignore()
{
	//return the number of "-" value in a cell.
	int rel = 0;
	for (int i = 0; i < _c.size(); i++)
	{
		if (_c[i] == '-')
			rel++;
	}
	return rel;
}

int Cell::size()
{
	return _c.size();
}

int Cell::findIgnore(int k)
{
	//return the k-th position of "-" value.
	for (int i = 0; i < _c.size(); i++)
	{
		if (_c[i] == '-')
		{
			k--;
			if (k == 0)
				return i;
		}
	}
	return -1;
}

bool Cell::isContain(const Cell & b)
{
	//check if this->cell contain cell b or not
	int count = 0;
	for (int i = 0; i < _type; i++)
	{
		if (_c[i] != '-')
		{
			if (_c[i] != b._c[i])
			{
				return false;
			}
		}
	}
	return true;

}

bool Cell::canAdd(const Cell & b,int type)
{
	//check if this->cell can be add with cell b
	//according to the agorithm.
	int count = 0;
	string temp = _c;
	for (int i = 0; i < type; i++)
	{

		if (_c[i] == b._c[i])
		{
			temp[i] = _c[i];
		}
		else
		{
			count++;
			temp[i] = '-';
		}
	}


	if (count <= 1)
	{
		_c = temp;
		return true;
	}
	else
		return false;
}



char & Cell::operator[](int i)
{
	//return the i-th character of cell
	if (i <= _c.size() - 1)
	{
		return _c[i];
	}
	else return _c[0];
}

bool Cell::isAdded()
{
	//check if the cell is add with another cell or not
	if (_isCong) return true;
	return false;
}


Cell Cell::operator+(const char c)
{
	Cell rel(*this);
	rel._c += c;
	return rel;
}





Cell & Cell::operator+=(const char c)
{
	_c += c;
	return *this;
}

Cell & Cell::operator=(const Cell & b)
{
	_c = b._c;
	_type = b._type;
	return *this;
	
}

bool Cell::operator==(const Cell & b)
{
	if (strcmp(_c.c_str(), b._c.c_str()) == 0) return true;
	return false;
}

void Cell::convert()
{
	//turn the cell from binary value to character value
	Cell rel;
	for (int i = 0; i < _type; i++)
	{
		if (_c[i] == '-')
		{

		}
		else
		{
			char temp = char(i + 'a');
			rel._c.push_back(temp);
			if (_c[i] == '0')
			{
				char a_temp = char(' ' + 7);
				rel._c.push_back(a_temp);

			}

		}
	}
	this->_c = rel._c;
}

bool Cell::isEmpty()
{

	if (_c.empty()) return true;
	return false;
}


Cell::~Cell()
{
	while (!_c.empty())
	{
		_c.pop_back();
	}
}

ostream & operator<<(ostream & out, const Cell & b)
{
	for (int i = 0; i < b._c.size(); i++)
	{
		out << b._c[i];
	}
	return out;
	// TODO: insert return statement here
}
