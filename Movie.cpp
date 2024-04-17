#include "Movie.h"
#include "Loans.h"

using namespace std;

//***********

//MOVIE CLASS

//***********



//************
//CONSTRUCTORS
//************

//*** Default Constructor ***
Movie::Movie() {
	movieID = 0;
	title = "";
	releaseDate = 0;
	rating = "";
	duration = 0;
	rentCost = 0;
	replaceCost = 0;
}

//*** Fully Defined Constructor ***
Movie::Movie(int movieID, string title, int releaseDate, string rating, int duration, float rentCost, float replaceCost) {
	this->movieID = movieID;
	this->title = title;
	this->releaseDate = releaseDate;
	this->rating = rating;
	this->duration = duration;
	this->rentCost = rentCost;
	this->replaceCost = replaceCost;
}



//*********
//ACCESSORS
//*********

int Movie::getMovieID() {
	return movieID;
}

string Movie::getTitle() {
	return title;
}

int Movie::getReleaseDate() {
	return releaseDate;
}

string Movie::getRating() {
	return rating;
}

int Movie::getDuration() {
	return duration;
}

float Movie::getRentCost() {
	return rentCost;
}

float Movie::getReplaceCost() {
	return replaceCost;
}

vector<Loan> Movie::getLoans() {
	return loans;
}



//********
//MUTATORS
//********

void Movie::setMovieID(int movieID) {
	this->movieID = movieID;
}

void Movie::setTitle(string title) {
	this->title = title;
}

void Movie::setReleaseDate(int date) {
	this->releaseDate = date;
}

void Movie::setRating(string rating) {
	this->rating = rating;
}

void Movie::setDuration(int duration) {
	this->duration = duration;
}

void Movie::setRentCost(float cost) {
	this->rentCost = cost;
}

void Movie::setReplaceCost(float cost) {
	this->replaceCost = cost;
}

void Movie::addLoan(Loan loan) {
	loans.push_back(loan);
}

void Movie::removeLoan(int id) {
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


//*** Print Info***
void Movie::print() {
	cout << endl;
	cout << "Movie ID: " << movieID << endl;
	cout << "Title: " << title << endl;
	cout << "Release Date: " << releaseDate << endl;
	cout << "Rating: " << rating << endl;
	cout << "Duration: " << duration << "m" << endl;
	cout << "Rent Cost: $" << rentCost << endl;
	cout << "Replacement Cost: $" << replaceCost << endl;
}