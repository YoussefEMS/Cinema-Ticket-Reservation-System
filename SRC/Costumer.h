#pragma once
#include "Person.h"
#include "Reservation.h"
#include "VIPhall.h"
#include "seat.h"
#include "Movie.h"
#include "snacks.h"
class Costumer : public Person
{private:
	string* data = new string[100];
	int counter = 0;
	bool button = false;
	Reservation R;
	Movie movies[5];
	int currentcheck = 0;
	static const int numberOfSnacks = 3;
	snacks snack[numberOfSnacks];
	Reservation currentSessionReservations[100];
	int currentSessionReservationsCount;
public:
	Costumer(string) ;
	void writeTicketToFile(hall*, char, int , string);
	void updateHallFile(const string, const string& , const char&,const int&);
	void Reserve_seat(string , int , string);
	bool displaymovieinfo(const string&);
	int readMoviesFromFile();
	void displaymovies();
	void readReservedSeats(const string& , const string& , hall* );
	void cancelReservation();
	int getcurrentcheck();
	void buySnacks();
	void readSnacks();
	void cancelRecentReservations();
	void checkAndUpdateTickets();
	bool ValidateMovie(string);
	~Costumer();

};

