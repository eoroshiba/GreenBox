#include "Loan.h"
#include "Loans.h"

using namespace std;

//***********
//
//LOANS CLASS
//
//***********



//*** Default Constructor ***
Loans::Loans() {
	count = 0;
}



//*** ACCESSOR ***
vector<Loan> & Loans::getLoans() {
	return loans;
}



//*** Add Loan ***
void Loans::addLoan(Loan toAdd) {

	//*Take Loan as argument, add Loan to collection
	loans.push_back(toAdd);
}



//*** Edit Loan***
void Loans::editLoan(int ID, string status) {

	//*Take Loan ID and new status as arguments
	//*Use Find Loan to find Loan
	Loan* toEdit = &*findLoan(ID);

	//*Change status to new status
	toEdit->setStatus(status);
}



//*** Delete Loan ***
void Loans::deleteLoan(int ID) {

	//*Take Loan ID as argument
	//*Use Find Loan to find loan and remove Loan from collection
	loans.erase(findLoan(ID));
}



//*** Find Loan ***
vector<Loan>::iterator Loans::findLoan(int ID) {

	//*Take Loan ID as argument
	//*Use for loop to iterate through collection until ID matches
	vector<Loan>::iterator i = loans.begin();
	for (i; i != loans.end(); i++) {
		if (i->getLoanID() == ID) {
			return i;
		}
	}

	//return index of Loan (loans.end() if not found)
	return i;
}



//*** Print Loans ***
void Loans::printLoans() {

	//*Use For loop to iterate through loans colection
	for (Loan x : loans) {

		//*Call each Loan's print method
		x.print();
	}
}



//*** Print Loan ***
void Loans::printLoan(int ID) {

	//*Take Loan ID as argument
	//*Use Find Loan to find Loan and call its print method
	(*findLoan(ID)).print();
}



//*** Print Active Loans ***
void Loans::printActive() {

	//*Use For loop to iterate through collection
	for (Loan x : loans) {

		//*If status is "Active", call the Loan's print method
		if (x.getStatus().compare("Active") == 0) {
			x.print();
		}
	}
}



//*** Print Completed Loans ***
void Loans::printCompleted() {

	//*Use For loop to iterate through Loans collection
	for (Loan x : loans) {

		//*If "Completed" status, call Loan's print function
		if (x.getStatus().compare("Completed") == 0) {
			x.print();
		}
	}
}



//*** Print Lost/Overdue Loans ***
void Loans::printLost() {

	//*Use for loop to iterate through Loans collection
	for (Loan x : loans) {

		//*Check each loan for "Overdue" or "Lost" status
		//*If Overdue or Lost, call the Loan's print method
		if (x.getStatus().compare("Overdue") == 0) {
			x.print();
		}
		else if (x.getStatus().compare("Lost") == 0) {
			x.print();
		}
	}
}



//*** Read Data ***
void Loans::read() {

	//*Open input file
	ifstream input("Loans.txt");

	//*Create line and word variables
	string line;
	string var;

	//*Open while loop ending when there are no lines left
	while (getline(input, line)) {

		//*Create string stream from get line
		istringstream in(line);
		
		//*Create temporary variables for Loan
		int loanID;
		int movieID;
		int custID;
		string dueDate;
		tm dueTime;
			int month;
			int day;
			int year;
			int hour;
			int minute;
			int seconds;
		string status;

		//*Input line contents to temporary variables
		in >> loanID;
		in >> movieID;
		in >> custID;
		in >> month;
		in >> day;
		in >> year;
		in >> hour;
		in >> minute;
		in >> seconds;
		in >> status;

		//*Set Due Time attributes
		dueTime.tm_mon = (month-1);
		dueTime.tm_mday = day;
		dueTime.tm_year = (year-1900);
		dueTime.tm_hour = hour;
		dueTime.tm_min = minute;
		dueTime.tm_sec = seconds;

		//*Set Due Date variable
		dueDate = "" + to_string(dueTime.tm_mon + 1) + "/" + to_string(dueTime.tm_mday) + "/" + to_string(dueTime.tm_year + 1900);

		//*Create Loan object using temporary variables and add to collection
		Loan toAdd(loanID, movieID, custID, dueDate, dueTime, status);
		loans.push_back(toAdd);
	}

	//*Set loan count
	count = loans.size();

	//*Close file
	input.close();
	
}



//*** Write Data ***
void Loans::write() {

	//*Open output file
	ofstream output("Loans.txt");

	//*Loop through Loans collection
	for (Loan x : loans) {

		//*Output variables into output file
		tm t = x.getDueTime();
		output << x.getLoanID() << " ";
		output << x.getMovieID() << " ";
		output << x.getCustID() <<  " ";
		output << (t.tm_mon + 1) <<  " ";
		output << t.tm_mday <<  " ";
		output << (t.tm_year + 1900) <<  " ";
		output << t.tm_hour <<  " ";
		output << t.tm_min <<  " ";
		output << t.tm_sec <<  " ";
		output << x.getStatus() << endl;
	}

	//*Close output file
	output.close();
}