#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Loan.h"

using namespace std;

//***********
//LOANS HEADER
//***********

class Loans {

//ATTRIBUTES
private:
	int count;
	vector<Loan> loans;

//METHODS
public:

	Loans();

	//Get Loans
	vector<Loan> & getLoans();

	//Editing Loans
	void addLoan(Loan);
	void editLoan(int, string);
	void deleteLoan(int);
	vector<Loan>::iterator findLoan(int);

	//Printing Information
	void printLoans();
	void printLoan(int);
	void printActive();
	void printCompleted();
	void printLost();

	//Reading and Writing Data
	void read();
	void write();
};