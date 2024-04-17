#include "Customer.h"
#include "Loans.h"

using namespace std;

//**************
//
//CUSTOMER CLASS
//
//**************



//************
//CONSTRUCTORS
//************

//*** Default Constructor ***
Customer::Customer() {
	custID = 0;
	cardNum = 0;
	name = "";
	cardExp = "";
	cvv = 0;
	movieNum = 0;
}

//*** Defined Constructor ***
Customer::Customer(int custID, double cardNum, string name, string cardExp, int cvv, int movieNum) {
	this->custID = custID;
	this->cardNum = cardNum;
	this->name = name;
	this->cardExp = cardExp;
	this->cvv = cvv;
	this->movieNum = movieNum;
}



//*********
//ACCESSORS
//*********

int Customer::getCustID() {
	return custID;
}

double Customer::getCardNum() {
	return cardNum;
}

string Customer::getName() {
	return name;
}

string Customer::getCardExp() {
	return cardExp;
}

int Customer::getCvv() {
	return cvv;
}

int Customer::getMovieNum() {
	return movieNum;
}

vector<Loan> Customer::getLoans() {
	return loans;
}



//********
//MUTATORS
//********

void Customer::setCustID(int custID) {
	this->custID = custID;
}

void Customer::setCardNum(double cardNum) {
	this->cardNum = cardNum;
}

void Customer::setName(string name) {
	this->name = name;
}

void Customer::setCardExp(string date) {
	this->cardExp = date;
}

void Customer::setCvv(int cvv) {
	this->cvv = cvv;
}

void Customer::setMovieNum(int movieNum) {
	this->movieNum = movieNum;
}

void Customer::addLoan(Loan loan) {
	loans.push_back(loan);
}

void Customer::removeLoan(int id) {
	vector<Loan>::iterator i = loans.begin();
	for (i; i != loans.end(); i++) {
		if ((*i).getLoanID() == id) {
			loans.erase(i);
			return;
		}
	}
}



//*************
//OTHER METHODS
//*************

//*** Print Info ***
void Customer::print() {
	cout << endl;
	cout << "Name: " << name << endl;
	cout << "ID: " << custID << endl;
	cout << "Number of Movies Out: " << movieNum << endl;
}