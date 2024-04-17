#pragma once
#include <iostream>
#include "Loans.h"

using namespace std;

//************
//MOVIE HEADER
//************

class Movie {

//ATTIRBUTES
private:
	int movieID;
	string title;
	int releaseDate;
	string rating;
	int duration;
	float rentCost;
	float replaceCost;
	vector<Loan> loans;

//METHODS
public:
	
	//CONSTRUCTORS
	Movie();
	Movie(int, string, int, string, int, float, float);

	//ACCESSORS
	int getMovieID();
	string getTitle();
	int getReleaseDate();
	string getRating();
	int getDuration();
	float getRentCost();
	float getReplaceCost();
	vector<Loan> getLoans();

	//MUTATORS
	void setMovieID(int);
	void setTitle(string);
	void setReleaseDate(int);
	void setRating(string);
	void setDuration(int);
	void setRentCost(float);
	void setReplaceCost(float);
	void addLoan(Loan);
	void removeLoan(int);

	//PRINT MOVIE
	void print();
};