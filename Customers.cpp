#include "Customers.h"
#include "Customer.h"

using namespace std;

//***************
//
//CUSTOMERS CLASS
//
//***************




//*** Dafault Constructor ***
Customers::Customers() {
	count = 0;
}




//*** Add Customer ***
string Customers::addCustomer() {

	//*Create temporary variables
	int tempID;
	string tempName;
	double tempCardNum;
	string tempCardExp;
	int tempCvv;

	//*Prompt user for name and direct input to name
	cout << endl;
	cout << "What is the customer's name? (First and last)" << endl;
	cin.ignore();
	getline(cin, tempName);

	//*Prompt user for card number and direct input to card number
	cout << "What is the customer's card number?" << endl;
	cin >> tempCardNum;

	//*Prompt user for card exp. and direct input to card exp.
	cout << "When does this card expire? (mm/yy)" << endl;
	cin >> tempCardExp;

	//*Prompt user for CVV and direct input to CVV
	cout << "What is the CVV for this card?" << endl;
	cin >> tempCvv;

	//*Assign Customer ID
	if (customers.size() == 0) {
		tempID = count + 1;
	}

	else {
		tempID = (*(customers.end()-1)).getCustID() + 1;
	}

	//*Create and populate customer object
	Customer temp = Customer(tempID, tempCardNum, tempName, tempCardExp, tempCvv, 0);

	//*Add to customer collection
	customers.push_back(temp);

	//*Increment count
	count++;

	//*Return customer name
	return tempName;
}



//*** Edit Customer ***
void Customers::editCustomer() {

	//*Prompt user for name and collect input
	string name;
	cout << endl << "What is the name of the customer you would like to edit? (First and last)" << endl;
	cin.ignore();
	getline(cin, name);
	if (findCustomer(name) == customers.end()) {
		cout << endl << "Customer not found" << endl;
		return;
	}

	//*Use find customer to find customer
	vector<Customer>::iterator toEdit = findCustomer(name);
	
	//*Prompt user for what field they would like to edit
	cout << endl << "What action would you like to perform?" << endl;
	cout << "1. Edit customer name" << endl;
	cout << "2. Edit card number" << endl;
	cout << "3. Edit card expiration" << endl;
	cout << "4. Edit CVV" << endl;
	cout << "5. Delete customer" << endl;
	int choice;
	cin >> choice;

	//*Make Edits to information
	switch(choice) {

	case 1: {
		cout << endl << "What is the new customer name? (First and last)" << endl;
		cin.ignore();
		string newName;
		getline(cin, newName);
		toEdit->setName(newName);
		break;
	}

	case 2: {
		cout << endl << "What is the new card number?" << endl;
		double cardNum;
		cin >> cardNum;
		toEdit->setCardNum(cardNum);
		break;
	}

	case 3: {
		cout << endl << "What is the new card expiration? (mm/yy)" << endl;
		string date;
		cin >> date;
		toEdit->setCardExp(date);
		break;
	}

	case 4: {
		cout << endl << "What is the new CVV?" << endl;
		int cvv;
		cin >> cvv;
		toEdit->setCvv(cvv);
		break;
	}


	case 5: {
		cout << endl << "Are you sure you want to delete " << toEdit->getName() << "?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		int input;
		cin >> input;
		if (input == 1) {
			deleteCustomer(toEdit);
		}
		break;
	}


	default:
		cout << endl << "Invalid input" << endl;
		break;
	}
}



//*** Delete Customer ***
void Customers::deleteCustomer(vector<Customer>::iterator toDel) {

	//*Take index as argument and remove customer from collection
	customers.erase(toDel);
}



//*** Find Customer by Name***
vector<Customer>::iterator Customers::findCustomer(string name) {
	
	//*Take name as argument and use loop to search through collection until name matches
	vector<Customer>::iterator i = customers.begin();
	for (i; i != customers.end(); i++) {
		if (i->getName().compare(name) == 0) {
			return i;
		}
	}

	//*Return index of customer
	return i;
}

//*** Find Customer by ID***
vector<Customer>::iterator Customers::findCustomer(int id) {

	//*Take ID as argument and use loop to search through collection until ID matches
	vector<Customer>::iterator i = customers.begin();
	for (i; i != customers.end(); i++) {
		if (i->getCustID() == id) {
			return i;
		}
	}

	//*Return index of customer
	return i;
}



//*** Print Customers ***
void Customers::printCustomers() {
	
	//*Use for loop to iterate through collection
	for (Customer x : customers) {
		//*Call each customer's print method
		x.print();
	}
}



//*** Print Customer ***
void Customers::printCustomer(string name) {
	
	//*Take name as argument and use find customer to find customer
	//*Call costumer's print method
	(*findCustomer(name)).print();
}



//*** Print Loans ***
void Customers::printLoans(string name) {

	//*Take name as argument
	//*Use find customer to find customer
	Customer cust = *findCustomer(name);

	//*Get loans for customer
	vector<Loan> loans = cust.getLoans();

	//*Use for loop to iterate through loans, calling each's print method
	for (Loan x : loans) {
		x.print();
	}
}



//*** Read Data ***
void Customers::read(vector<Loan>* loans) {

	//*Take Loan vector as argument
	//*Open input file stream
	ifstream input("Customers.txt");

	//*Declare line and word variables
	string line;
	string var;

	//*Open while loop ending when there are no lines left
	while (getline(input, line)) {

		//*Open input stream from get line
		istringstream in(line);

		//*Creat temporary variables for customer
		int custID;
		double cardNum;
		string name;
		string cardExp;
		int cvv;
		int movieNum;

		//*Read in variables from file
		in >> custID;
		in >> cardNum;
		in >> name;
		in >> cardExp;
		in >> cvv;
		in >> movieNum;
		replace(name.begin(), name.end(), '_', ' ');

		//*Create temporary customer with given variables
		Customer toAdd(custID, cardNum, name, cardExp, cvv, movieNum);

		//*Loop through Loan vector to determine if IDs match
		for (Loan x : *loans) {

			//*If IDs match, add Loan pointer to customer loans
			if (x.getCustID() == custID && (x.getStatus().compare("Completed") != 0 && x.getStatus().compare("Lost") != 0))
				toAdd.addLoan(x);
		}
		
		//*Add customer to vector
		customers.push_back(toAdd);
	}

	//*Set count to vector size
	count = customers.size();

	//*Close input file
	input.close();
}



//*** Write Data ***
void Customers::write() {

	//*Open output file
	ofstream output("Customers.txt");

	//*Loop through customers vector
	for (Customer x : customers) {

		//*Output each variable in output file on one line
		string name = x.getName();
		replace(name.begin(), name.end(), ' ', '_');
		output << fixed;
		output << x.getCustID() << " ";
		output << x.getCardNum() << " ";
		output << name << " ";
		output << x.getCardExp() << " ";
		output << x.getCvv() << " ";
		output << x.getMovieNum() << endl;
	}

	//*Close ouput file
	output.close();
}