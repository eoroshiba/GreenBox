#include "Movie.h"
#include "Movies.h"
#include "Loans.h"

using namespace std;

//************
//
//MOVIES CLASS
//
//************




//*** Default Constructor ***
Movies::Movies() {
	count = 0;
}

//*** Get Movies ***
vector<Movie> Movies::getMovies() {
	return movies;
}
//*** Add Movie ***
void Movies::addMovie() {

	//*Create temporary variables for Movie
	int movieID;
	string title;
	int releaseDate;
	string rating;
	int duration;
	float rentCost;
	float replaceCost;

	//*Prompt user for variables and store them accordingly
	cout << endl;
	cout << "What is the name of the movie you would like to add?" << endl;
	cin.ignore();
	getline(cin, title);
	cout << "What is the release date of this movie? (yyyy)" << endl;
	cin >> releaseDate;
	cout << "What is the rating of this movie?" << endl;
	cin >> rating;
	cout << "What is the duration (in minutes) of this movie?" << endl;
	cin >> duration;
	cout << "What is the rental cost of this movie?" << endl;
	cin >> rentCost;
	cout << "What is the replacement cost of this movie?" << endl;
	cin >> replaceCost;

	//*Set Movie ID
	if (movies.size() == 0) {
		movieID = count + 1;
	}

	else {
		movieID = (*(movies.end() - 1)).getMovieID() + 1;
	}

	//*Create Movie object using temporary variables
	Movie toAdd(movieID, title, releaseDate, rating, duration, rentCost, replaceCost);

	//*Put movie in collection
	movies.push_back(toAdd);

	//*Increment Movie count
	count++;
	
}



//*** Edit Movie ***
void Movies::editMovie() {

	//*Prompt user for Movie ID
	cout << endl;
	cout << "What is the ID of the movie you would like to edit?" << endl;
	int id;
	cin >> id;

	//*Use Find Movie to find movie
	vector<Movie>::iterator movie = findMovie(id);

	//*Prompt user for which field they would like to edit
	cout << endl;
	cout << "What would you like to edit about this movie?" << endl;
	cout << "1. Title" << endl;
	cout << "2. Release Date" << endl;
	cout << "3. Rating" << endl;
	cout << "4. Duration" << endl;
	cout << "5. Rental Cost" << endl;
	cout << "6. Replacement Cost" << endl;
	cout << "7. Delete Movie" << endl;

	//*Make appropriate edits
	int choice;
	cin >> choice;
	switch (choice) {

	case 1: {
		string tempTitle;
		cout << endl << "What would you like the new title to be?" << endl;
		cin >> tempTitle;
		movie->setTitle(tempTitle);
		break;
	}

	case 2: {
		int date;
		cout << endl << "What would you like the new release date to be? (yyyy)" << endl;
		cin >> date;
		movie->setReleaseDate(date);
		break;
	}

	case 3: {
		string rating;
		cout << endl << "What would you like the new rating to be?" << endl;
		cin >> rating;
		movie->setRating(rating);
		break;
	}

	case 4: {
		int duration;
		cout << endl << "What would you like the new duration to be? (in minutes)" << endl;
		cin >> duration;
		movie->setDuration(duration);
		break;
	}

	case 5: {
		float cost;
		cout << endl << "What would you like the new rental cost to be?" << endl;
		cin >> cost;
		movie->setRentCost(cost);
		break;
	}

	case 6: {
		float cost;
		cout << endl << "What would you like the new replacement cost to be?" << endl;
		cin >> cost;
		movie->setReplaceCost(cost);
		break;
	}
		  
	case 7: {
		int input;
		cout << endl << "Are you sure you would like to delete this movie?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cin >> input;
		if (input == 1)
			deleteMovie(movie);
	}

	default: {
		cout << endl << "Invalid input" << endl;
	}
	}
}



//*** Delete Movie ***
void Movies::deleteMovie(vector<Movie>::iterator toDel) {

	//*Take Movie ID as argument
	//*Remove movie from collection
	movies.erase(toDel);
}



//*** Find Movie ***
vector<Movie>::iterator Movies::findMovie(int id) {

	//*Take Movie ID as argument
	//*Use for loop to iterate through movies until match is found
	vector<Movie>::iterator i = movies.begin();
	for (i; i != movies.end(); i++) {
		if (i->getMovieID() == id)
			return i;
	}

	//*Return index of movie
	return i;
}



//*** Print Movies ***
void Movies::printMovies() {

	//*Use for loop to iterate through collection
	for (Movie x : movies) {

		//*For each movie, call print method
		x.print();
	}
}



//*** Print Movie ***
void Movies::printMovie(int id) {

	//*Take Movie ID as argument and use Find Movie to find movie
	//*Call Movie's print method
	findMovie(id)->print();
}



//*** Print Loans ***
void Movies::printLoans(int id) {

	//*Use for loop to iterate through loans for given movie
	vector<Loan> loans = findMovie(id)->getLoans();
	cout << endl << "Loans for move ID " << id << endl;
	for (Loan x : loans) {

		//*Call each Loan's print method
		x.print();
	}
}



//*** Read Data ***
void Movies::read(vector<Loan>* loans) {

	//*Take in Loan vector as argument
	//*Open input stream
	ifstream input("Movies.txt");

	//*Declare line and word variables
	string line;
	string var;

	//*Open while loop ending when there are no lines left
	while (getline(input, line)) {

		//*Open input stream from get line
		istringstream in(line);

		//*Create temporary variables for Movie
		int movieID;
		string title;
		int releaseDate;
		string rating;
		int duration;
		float rentCost;
		float replaceCost;

		//*Read in variables from file
		in >> movieID;
		in >> title;
		in >> releaseDate;
		in >> rating;
		in >> duration;
		in >> rentCost;
		in >> replaceCost;

		//*Creat temporary movie with given variables
		replace(title.begin(), title.end(), '_', ' ');
		Movie toAdd(movieID, title, releaseDate, rating, duration, rentCost, replaceCost);

		//*Loop through Loan vector to determine if IDs match
		for (Loan x : *loans) {

			//*If IDs match, add Loan pointer to Movie loans
			if (x.getMovieID() == movieID) {
				toAdd.addLoan(x);
			}
		}

		//*Add movie to vector
		movies.push_back(toAdd);
	}

	//*Set count to vector size
	count = movies.size();

	//*Close input file
	input.close();
}



//*** Write Data ***
void Movies::write() {

	//*Open outut file
	ofstream output("Movies.txt");

	//*Loop through Movies vector
	for (Movie x : movies) {

		//*Output each variable in one line of output file
		string title = x.getTitle();
		replace(title.begin(), title.end(), ' ', '_');
		output << x.getMovieID() << " ";
		output << title << " ";
		output << x.getReleaseDate() << " ";
		output << x.getRating() << " ";
		output << x.getDuration() << " ";
		output << x.getRentCost() << " ";
		output << x.getReplaceCost() << endl;
	}

	//*Close output file
	output.close();
}