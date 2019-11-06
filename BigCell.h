#pragma once
#include "Cell.h"
#include <iostream>
#include <stdio.h>
class BigCell
{
private:
	int _n;
	vector<Cell> _big;
public:
	BigCell();

	BigCell(const BigCell &b);
	//because the cell added to bigcell can have the _type = 0, so we need to redefine it.
	void defineType(int type);
	//check if cell b is in bigcell.
	void check(Cell b);

	void turnOn(Cell b);
	//convert cell into binary value
	void handleOneInput(Cell b);
	//convert all input into binary value
	void handleInput(BigCell b);
	//remove i-th value
	void pop(int i);

	void sortBy1();
	
	void removeAllMark();
	//add cell b
	void copyCell(const BigCell &b);

	BigCell removeSmaller();

	//input is the smallcell and the output is where to save the prime implicants
	//the bigcell call this function must be the big cells 
	BigCell findThePrimeCell(BigCell &smallcell,BigCell &output);

	////the bigcell call this function must be the big cells 
	bool isFullyCover(BigCell smallCell);

	//the bigcell call this function must be the big cells 
	void removeBigAndSmallCells(BigCell &small, int k);

	//the bigcell call this function must be the big cells 
	//temp1 is where to save the implicants we consider as prime. 
	//alternative is where to save all the temp1
	void findAlternative(BigCell SmallerCell, BigCell &temp, vector<BigCell> &alternative);

	//the bigcell call this must be the first small cells which have been convert to binary value
	BigCell allTheBigCell();

	//output is to save the prime implicants
	vector<BigCell> booleanMinimizer(BigCell firstSmallCell,BigCell &output);

	void sortMotherCell(BigCell smallcell);

	//convert output to char value
	void covertOutput();

	BigCell& operator=(const BigCell &b);

	bool empty();

	friend istream& operator>> (istream &in, BigCell &b);
	
	friend ostream& operator<< (ostream &out,const BigCell &b);

	~BigCell();
};

