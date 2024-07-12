#pragma once
#include "seat.h"
#include<iostream>
class hall
{
protected:
	seat*** seats;
	std::string hallname;
	double ticketprice;
	seat* reservedseats;
public:
	hall();
	std::string getname();
	double getticketprice() const;
	~hall();
	void displayavailableseats();
	int reserve(char, int);
};
