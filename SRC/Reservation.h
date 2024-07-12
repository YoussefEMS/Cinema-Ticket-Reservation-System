#pragma once
#include "seat.h"
#include "hall.h"
#include <iostream>
using namespace std;
class Reservation
{
	string movietitle,halltype;
	char seatrow;
	int seatcolumn;
public:
	void setter(string, string, char, int);
	string getmovietitle() const;
	string gethalltype() const;
	char getseatrow() const;
	int getcolumn() const;
};

