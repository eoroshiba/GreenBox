GreenBox : main.o Customer.o Customers.o Loan.o Loans.o Movie.o Movies.o
	g++ -o GreenBox main.o Customer.o Customers.o Loan.o Loans.o Movie.o Movies.o

main.o : main.cpp Customer.h Customers.h Loan.h Loans.h Movie.h Movies.h
	g++ -c main.cpp

Customer.o : Customer.cpp Customer.h Loan.h
	g++ -c Customer.cpp

Customers.o : Customers.cpp Customers.h Customer.h Loan.h
	g++ -c Customers.cpp

Loan.o : Loan.cpp Loan.h
	g++ -c Loan.cpp

Loans.o : Loan.cpp Loan.h Loans.cpp Loans.h
	g++ -c Loans.cpp

Movie.o : Movie.cpp Movie.h Loan.h
	g++ -c Movie.cpp

Movies.o : Movie.h Movies.cpp Movies.h Loan.h
	g++ -c Movies.cpp

clean :
	rm *.o GreenBox