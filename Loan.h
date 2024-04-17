#pragma once
#include<iostream>
#include <time.h>

using namespace std;

//**********
//LOAN HEADER
//**********

class Loan {

//ATTRIBUTES
private:
	int loanID;
	int movieID;
	int custID;
	string dueDate;
	tm dueTime;
	string status;

//FUNCTIONS
public:

	//CONSTRUCTORS
	Loan();
	Loan(int, int, int, string, tm, string);

	//ACCESSORS
	int getLoanID();
	int getMovieID();
	int getCustID();
	string getDueDate();
	tm& getDueTime();
	string getStatus();

	//MUTATORS
	void setLoanID(int);
	void setMovieID(int);
	void setCustID(int);
	void setDueDate(string);
	void setDueTime(tm);
	void setStatus(string);


	//PRINT LOAN
	void print();
};