/*
***********************************************************************************************************************************************
***********************************************************************************************************************************************
*
*   Name: Ethan Oroshiba
*   Class: CSCE 1040.003
*   Assignment: Homework 2
*
***********************************************************************************************************************************************
***********************************************************************************************************************************************
*/


//*************
//
//    MAIN
//
//*************



//************
//DEPENDENCIES
//************

#include <set>
#include "Customer.h"
#include "Customers.h"
#include "Loan.h"
#include "Loans.h"
#include "Movie.h"
#include "Movies.h"

using namespace std;

//**********************
// FUNCTION DECLARATION
//**********************

void checkTime(Loans&);
void checkOutMovie(Customers&, Loans&, Movies&);
void returnMovie(Customers&, Loans&, Movies&);
void reportLost(Customers&, Loans&, Movies&);
void admin(Customers&, Loans&, Movies&);



//******
// MAIN
//******

int main() {
	Loans loans;
	Customers customers;
	Movies movies;
	loans.read();
	customers.read(&loans.getLoans());
	movies.read(&loans.getLoans());

	int mainMenu = 0;
	while (mainMenu != -1) {
		checkTime(loans);
		cout << endl;
		cout << "~~~~~~~~~" << endl;
		cout << "MAIN MENU" << endl << "~~~~~~~~~"  << endl << endl;
		cout << "Enter the number of the action you would like to perform:" << endl;
		cout << "1. Check out movie" << endl;
		cout << "2. Return movie" << endl;
		cout << "3. Edit Customer Details" << endl;
		cout << "4. Report lost movie" << endl;
		cout << "5. Admin Login" << endl;
		cout << "Enter -1 to quit" << endl;
		
		cin >> mainMenu;

		switch (mainMenu) {

		case -1: {
			break;
		}

		case 1: {
			checkTime(loans);
			checkOutMovie(customers, loans, movies);
			customers.write();
			loans.write();
			movies.write();
			checkTime(loans);
			break;
		}

		case 2: {
			checkTime(loans);
			returnMovie(customers, loans, movies);
			customers.write();
			loans.write();
			movies.write();
			checkTime(loans);
			break;
		}

		case 3: {
			checkTime(loans);
			customers.editCustomer();
			customers.write();
			checkTime(loans);
			break;
		}

		case 4: {
			checkTime(loans);
			reportLost(customers, loans, movies);
			customers.write();
			loans.write();
			movies.write();
			checkTime(loans);
			break;
		}

		case 5: {
			checkTime(loans);
			admin(customers, loans, movies);
			customers.write();
			loans.write();
			movies.write();
			checkTime(loans);
			break;
		}

		default: {
			cout << endl << "Invalid input" << endl;
			break;
		}

		}
	}
}





//*********
//FUNCTIONS
//*********



//*** Check Time *** - Updates Loans
void checkTime(Loans &loans) {

	//*Get current time
	time_t currTime = time(NULL);

	//*Get loans
	vector<Loan> loanCollection = loans.getLoans();

	//*For each loan in loans, compare due time to current time
	for (Loan x : loanCollection) {
		time_t dueTime = mktime(&x.getDueTime());
		string status = x.getStatus();
		//*If current time is greater than due time and loan is not complete, mark overdue
		if (difftime(currTime, dueTime) > 0 && status.compare("Complete") != 0) {
			int loanID = x.getLoanID();
			loans.editLoan(loanID, "Overdue");
		}
	}

}



//*** Check Out Movie ***
void checkOutMovie(Customers &customers, Loans &loans, Movies &movies) {
	cout << endl;
	cout << "******" << endl;
	cout << "MOVIES" << endl;
	cout << "******" << endl;

	//*Get movies
	vector<Movie> movieCollection = movies.getMovies();

	//*Create set for already listed movie names
	set<string> used;

	//*Use for loop to iterate through movies in movie collection
	for (Movie x : movieCollection) {

		//*Check if title has already been listed
		string title = x.getTitle();
		if (used.find(title) == used.end()) {
			bool toggle = true;

			//*Use for loop to iterate through loans and see if all are completed
			for (Loan l : x.getLoans()) {
				string status = l.getStatus();
				status.compare("Completed") == 0 ? toggle = true : toggle = false;
			}

			//*If all loans complete, print movie and insert title to used set
			if (toggle) {
				x.print();
				used.insert(title);
			}
		}
	}

	//*Prompt user for movie ID they would like to rent
	int movieID;
	cout << endl << "Enter the ID of the movie you would like to rent:" << endl;
	cin >> movieID;

	//*Prompt user for account information
	int acct;
	cout << endl << "Have you rented a movie with GreenBox before?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	cin >> acct;
	Customer* customer;
	if (acct == 1) {
		string name;
		cout << endl << "What is your name? (First and last)" << endl;
		cin.ignore();
		getline(cin, name);
		customer = &*customers.findCustomer(name);
		cout << endl << "Customer found" << endl;
	}
	else {
		string name = customers.addCustomer();
		customer = &*customers.findCustomer(name);
	}

	//*Check for more than two rented movies
	if (customer->getLoans().size() >= 2) {
		cout << endl << "We are sorry, but you cannot rent out any movies because you already have two or more active rentals" << endl;
		return;
	}

	//*Check for any overdue movies
	int overCount = 0;
	for (Loan l : customer->getLoans()) {
		if (l.getStatus().compare("Overdue") == 0)
			overCount++;
	}
	if (overCount > 0) {
		cout << endl << "We are sorry, but you cannot rent out any movies because you have one or more overdue movie" << endl;
		return;
	}

	//*Display movie cost and recieve payment
	float movieCost = movies.findMovie(movieID)->getRentCost();
	cout << endl << "Movie cost is $" << movieCost << endl;
	cout << "Please insert payment now" << endl;
	//Check if payment successful. If not, break

	//*Create loan object and populate
	int loanID;
	if (loans.getLoans().size() == 0)
		loanID = 1;
	else 
		loanID = (*(loans.getLoans().end() - 1)).getLoanID() + 1;
	int custID = customer->getCustID();
	time_t currTime = time(NULL);
	tm dueTime = *localtime(&currTime);
	dueTime.tm_mday = dueTime.tm_mday + 1;
	mktime(&dueTime);
	string dueDate = "" + to_string(dueTime.tm_mon + 1) + "/" + to_string(dueTime.tm_mday) + "/" + to_string(dueTime.tm_year + 1900);
	Loan loan(loanID, movieID, custID, dueDate, dueTime, "Active");

	//*Add loan to loans collection
	loans.addLoan(loan);

	//*Add loan pointer to customer and movie objects
	customer->addLoan(loan);
	movies.findMovie(movieID)->addLoan(loan);
	customer->setMovieNum(customer->getMovieNum() + 1);

	//*Output loan information
	cout << endl << "Payment successful" << endl;
	cout << endl << "Loan info:" << endl;
	loan.print();
	//Dispense movie
}



//*** Return Movie ***
void returnMovie(Customers& customers, Loans& loans, Movies& movies) {
	cout << endl;

	//*Prompt user for movie ID
	cout << "Enter the ID of the movie you are returning:" << endl;
	int movieID;
	cin >> movieID;

	//*Find loan matching movie ID
	vector<Loan> loanCollection = loans.getLoans();
	Loan loan;
	for (int i = loanCollection.size() - 1; i >= 0; i--) {
		Loan tempLoan = loanCollection[i];
		int loanMovieID = tempLoan.getMovieID();
		string status = tempLoan.getStatus();
		if (loanMovieID == movieID && (status.compare("Active") == 0 || status.compare("Overdue") == 0)) {
			loan = tempLoan;
			break;
		}
	}

	//*Get customer ID
	int loanID = loan.getLoanID();
	int custID = loan.getCustID();
	string status = loan.getStatus();


	//*If loan is overdue, charge late fee
	if (status.compare("Overdue") == 0) {
		cout << endl;
		cout << "Movie is overdue" << endl;

		//*Calculate late fee
		time_t currTime = time(NULL);
		time_t dueTime = mktime(&loan.getDueTime());
		int lateFee = 1 + ((int)(difftime(currTime, dueTime) / 86400));

		//*Charge late fee
		cout << "Late fee is $" << lateFee << endl;
		cout << "Insert payment now" << endl;
		//Check that payment goes through and if it does, continue
		cout << "Payment successful" << endl;
	}

	//*Recieve Movie
	cout << endl;
	cout << "Place movie in return slot" << endl;
	//Once movie is placed in return slot, continue

	customers.findCustomer(custID)->setMovieNum(customers.findCustomer(custID)->getMovieNum() - 1);
	//*Update loan status
	loans.editLoan(loanID, "Completed");

	//*Remove loan from customer object
	customers.findCustomer(custID)->removeLoan(loanID);

	//*Remove loan from movie object
	movies.findMovie(movieID)->removeLoan(loanID);
}



//*** Report Lost Movie ***
void reportLost(Customers& customers, Loans& loans, Movies& movies) {
	cout << endl;

	//*Get customer information
	string name;
	cout << "What is your name? (First and last)" << endl;
	cin.ignore();
	getline(cin, name);

	//*Find customer
	Customer cust = *customers.findCustomer(name);

	//*Display list of loans
	for (Loan x : cust.getLoans()) {
		string title = (*movies.findMovie(x.getMovieID())).getTitle();
		cout << endl;
		cout << "Movie Title: " << title << endl;
		cout << "Loan ID: " << x.getLoanID() << endl;
		cout << endl;
	}

	//*Prompt user for loan that is lost
	cout << "Enter Loan ID from list above:" << endl;
	int loanID;
	cin >> loanID;
	Loan loan = *loans.findLoan(loanID);

	//*Charge replacement cost
	float replaceCost = (*movies.findMovie(loan.getMovieID())).getReplaceCost();
	cout << endl << "Replacement cost is $" << replaceCost << endl;;
	cout << "Please insert payment now" << endl;
	//Check if payment goes through, if it does, continue

	//*Update loan status
	loans.editLoan(loanID, "Lost");
	cust.removeLoan(loanID);
	cout << "Payment successsful" << endl;
}



//*** Admin Portal ***
void admin(Customers& customers, Loans& loans, Movies& movies) {
	cout << endl << "Enter username: (abcd)" << endl;
	string user;
	cin >> user;
	cout << endl << "Enter password: (1234)" << endl;
	int password;
	cin >> password;
	if (user.compare("abcd") != 0 || password != 1234) {
		cout << endl << "Incorrect username and password combination entered" << endl;
		return;
	}

	cout << endl << "****** ADMIN PORTAL ******" << endl << endl;
	cout << "Enter the number of the collection you would like to edit" << endl;
	cout << "1. Customers" << endl;
	cout << "2. Loans" << endl;
	cout << "3. Movies" << endl;

	int choice;
	cin >> choice;

	switch (choice) {
		
	case 1: {
		cout << endl;
		cout << "Enter the number of the action you would like to perform:" << endl;
		cout << "1. Display customers" << endl;
		cout << "2. Add customer" << endl;
		cout << "3. Edit customer" << endl;
		cout << "4. Delete customer" << endl;

		int choice2;
		cin >> choice2;

		switch (choice2) {

		case 1: {
			cout << endl;
			customers.printCustomers();
			break;
		}

		case 2: {
			cout << endl;
			customers.addCustomer();
			break;
		}

		case 3: {
			cout << endl;
			customers.editCustomer();
			break;
		}

		case 4: {
			cout << endl;
			cout << "What is the name of the customer you would like to delete? (First and last)" << endl;
			string name;
			cin.ignore();
			getline(cin, name);
			customers.deleteCustomer(customers.findCustomer(name));
			break;
		}

		default: {
			cout << endl << "Invalid input" << endl;
			break;
		}
		}

		break;
	}

	case 2: {
		cout << endl;
		cout << "Enter the number of the action you would like to perform:" << endl;
		cout << "1. Display loans" << endl;
		cout << "2. Display active loans" << endl;
		cout << "3. Display completed loans" << endl;
		cout << "4. Display overdue/lost loans" << endl;
		cout << "5. Add loan" << endl;
		cout << "6. Edit loan" << endl;
		cout << "7. Delete loan" << endl;

		int choice2;
		cin >> choice2;

		switch (choice2) {

		case 1: {
			cout << endl;
			cout << "LOANS:" << endl;
			loans.printLoans();
			break;
		}

		case 2: {
			cout << endl;
			cout << "ACTIVE LOANS:" << endl;
			loans.printActive();
			break;
		}

		case 3: {
			cout << endl;
			cout << "COMPLETED LOANS:" << endl;
			loans.printCompleted();
			break;
		}

		case 4: {
			cout << endl;
			cout << "LOST AND OVERDUE LOANS:" << endl;
			loans.printLost();
			break;
		}

		case 5: {
			cout << endl;
			int loanID;
			int movieID;
			int custID;
			string dueDate;
			string timeToBeParsed;
			tm dueTime;
			int dueMonth;
			int dueDay;
			int dueYear;
			int dueHour;
			int dueMinutes;
			int dueSecs;
			string status;

			loanID = (*(loans.getLoans().end()-1)).getLoanID() + 1;
			cout << "What is the movie ID of the loan?" << endl;
			cin >> movieID;
			cout << "What is the customer ID of the loan?" << endl;
			cin >> custID;
			cout << "What is the date this loan is due? (mm/dd/yyyy)" << endl;
			cin >> dueDate;
			dueMonth = stoi(dueDate.substr(0, 2));
			dueDay = stoi(dueDate.substr(3, 5));
			dueYear = stoi(dueDate.substr(6, 10));
			cout << "What time is the loan due? (hh:mm:ss)" << endl;
			cin >> timeToBeParsed;
			dueHour = stoi(timeToBeParsed.substr(0, 2));
			dueMinutes = stoi(timeToBeParsed.substr(3, 5));
			dueSecs = stoi(timeToBeParsed.substr(6, 8));
			dueTime.tm_mon = dueMonth;
			dueTime.tm_mday = dueDay;
			dueTime.tm_year = dueYear;
			dueTime.tm_hour = dueHour;
			dueTime.tm_min = dueMinutes;
			dueTime.tm_sec = dueSecs;
			cout << "What is the status of this loan?" << endl;
			cin >> status;

			Loan loan(loanID, movieID, custID, dueDate, dueTime, status);
			loans.addLoan(loan);
			break;
		}

		case 6: {
			cout << endl << "What is the ID of the loan you would like to edit?" << endl;
			int id;
			cin >> id;
			cout << "What is the new status of this loan?" << endl;
			string status;
			cin >> status;
			loans.editLoan(id, status);
			break;
		}

		case 7: {
			cout << endl << "What is the ID of the loan you would like to delete?" << endl;
			int id;
			cin >> id;
			loans.deleteLoan(id);
			break;
		}

		default: {
			cout << endl << "Invalid input" << endl;
			break;
		}
		}

		break;
	}

	case 3: {
		cout << endl;
		cout << "Enter the number of the action you would like to perform" << endl;
		cout << "1. Display movies" << endl;
		cout << "2. Add movie" << endl;
		cout << "3. Edit movie" << endl;
		cout << "4. Delete movie" << endl;

		int choice2;
		cin >> choice2;

		switch (choice2) {

		case 1: {
			cout << endl;
			movies.printMovies();
			break;
		}

		case 2: {
			cout << endl;
			movies.addMovie();
			break;
		}

		case 3: {
			cout << endl;
			movies.editMovie();
			break;
		}

		case 4: {
			cout << endl << "What is the ID of the movie you would like to delete?" << endl;
			int id;
			cin >> id;
			movies.deleteMovie(movies.findMovie(id));
			break;
		}

		default: {
			cout << endl << "Invalid input" << endl;
			break;
		}
		}

		break;
	}
	
	default: {
		cout << endl << "Invalid input" << endl;
		break;
	}
	}
}