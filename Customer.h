#pragma once
#include <iostream>
#include <vector>
#include "Loans.h"

using namespace std;

//**************
//CUSTOMER HEADER
//**************

class Customer {

//ATTRIBUTES
private:
	int custID;
	double cardNum;
	string name;
	string cardExp;
	int cvv;
	int movieNum;
	vector<Loan> loans;


//METHODS
public:

	//CONSTRUCTORS
	Customer();
	Customer(int, double, string, string, int, int);

	//ACCESSORS
	int getCustID();
	double getCardNum();
	string getName();
	string getCardExp();
	int getCvv();
	int getMovieNum();
	vector<Loan> getLoans();

	//MUTATORS
	void setCustID(int);
	void setCardNum(double);
	void setName(string);
	void setCardExp(string);
	void setCvv(int);
	void setMovieNum(int);
	void addLoan(Loan);
	void removeLoan(int);

	//PRINT CUSTOMER
	void print();
};