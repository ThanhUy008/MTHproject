#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Cell
{
private:
	int _type;
	bool _isCong;
	string _c;
public:
	Cell();
	
	Cell(const string &b);
	
	Cell(const Cell &b);
	
	void pushback(char c);

	//after we add a cell with another, we need to mark it as added.
	void markAferAdd();
	//remove the mark with ' ' (space) to mark that as still can be add.
	void removeMark();
	//completely remove the mark so we dont confused.

	//get the mark (_c[_type]).

	void setType(int n);

	int& getType();
	//return the number of 1 value in cell.
	int n_1();
	//return the number of '-' value in cell.
	int n_ignore();

	int size();

	//return the index of the k-th '-' value
	int findIgnore(int k);
	//check if cell is contain cell b
	bool isContain(const Cell &b);
	//check if can add to cell b. if true, add and change the former cell
	bool canAdd(const Cell&b,int type);
	//add a string to the end former cell
	//get the i-th char of cell. 
	//Usefull in bigcell
	char& operator[] (int i);
	
	bool isAdded();


	Cell operator+(const char c);

	// add a char to the end of cell
	//uses in bigcell
	Cell& operator+=(const char c);
	
	Cell& operator=(const Cell &b);
	//compare two cell
	bool operator== (const Cell &b);
	//convert cell from binary value to string value
	void convert();

	friend ostream& operator<<(ostream& out, const Cell &b);

	bool isEmpty();

	~Cell();
};

