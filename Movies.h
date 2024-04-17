#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Movie.h"
#include "Loan.h"

using namespace std;

//************
//MOVIES HEADER
//************

class Movies {

//ATTRIBUTES
private:
	int count;
	vector<Movie> movies;

//METHODS
public:

	Movies();

	//Get Movies
	vector<Movie> getMovies();

	//Editing Movies
	void addMovie();
	void editMovie();
	void deleteMovie(vector<Movie>::iterator);
	vector<Movie>::iterator findMovie(int);

	//Printing Information
	void printMovies();
	void printMovie(int);
	void printLoans(int);

	//Reading and Writing Information
	void read(vector<Loan>* loans);
	void write();
};