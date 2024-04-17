#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Customer.h"
#include "Loans.h"

using namespace std;

//***************
//CUSTOMERS HEADER
//***************

class Customers {

//ATTRIBUTES
private:
	int count;
	vector<Customer> customers;

//METHODS
public:

	Customers();

	//Editing Customers
	string addCustomer();
	void editCustomer();
	void deleteCustomer(vector<Customer>::iterator);
	vector<Customer>::iterator findCustomer(string);
	vector<Customer>::iterator findCustomer(int);

	//Printing Information
	void printCustomers();
	void printCustomer(string);
	void printLoans(string);

	//Reading and Writing Data
	void read(vector<Loan>* loans);
	void write();
};