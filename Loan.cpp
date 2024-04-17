#include "Loan.h"

using namespace std;

//**********
//
//LOAN CLASS
//
//**********



//************
//CONSTRUCTORS
//************

//*** Default Constructor ***
Loan::Loan() {
	loanID = 0;
	movieID = 0;
	custID = 0;
	dueDate = "";
	dueTime = { 0 };
	status = "";
}

//*** Fully Defined Constructor ***
Loan::Loan(int loanID, int movieID, int custID, string dueDate, tm dueTime, string status) {
	this->loanID = loanID;
	this->movieID = movieID;
	this->custID = custID;
	this->dueDate = dueDate;
	this->dueTime = dueTime;
	this->status = status;
}



//*********
//ACCESSORS
//*********

int Loan::getLoanID() {
	return loanID;
}

int Loan::getMovieID() {
	return movieID;
}

int Loan::getCustID() {
	return custID;
}

string Loan::getDueDate() {
	return dueDate;
}

tm& Loan::getDueTime() {
	return dueTime;
}

string Loan::getStatus() {
	return status;
}



//********
//MUTATORS
//********

void Loan::setLoanID(int loanID) {
	this->loanID = loanID;
}

void Loan::setMovieID(int movieID) {
	this->movieID = movieID;
}

void Loan::setCustID(int custID) {
	this->custID = custID;
}

void Loan::setDueDate(string dueDate) {
	this->dueDate = dueDate;
}

void Loan::setDueTime(tm dueTime) {
	this->dueTime = dueTime;
}

void Loan::setStatus(string status) {
	this->status = status;
}


//******
//OTHERS
//******

//*** Print Info ***
void Loan::print() {
	cout << endl;
	cout << "Loan ID: " << loanID << endl;
	cout << "Movie ID: " << movieID << endl;
	cout << "Customer ID: " << custID << endl;
	cout << "Due Date: " << dueDate << endl;
	cout << "Due Time: " << dueTime.tm_hour << ":" << dueTime.tm_min << endl;
	cout << "Status: " << status << endl;
}