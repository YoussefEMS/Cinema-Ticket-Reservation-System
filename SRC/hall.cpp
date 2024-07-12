#include "hall.h"
#include "seat.h"
using namespace std;
#include<iostream>
hall::hall() {
	seats = new seat * *[5];
	for (int row = 0; row < 5; row++) {
		seats[row] = new seat * [10];
		for (int column = 0; column < 10; column++) {
			seats[row][column] = new seat(static_cast<char>('A' + row), column);
		}
	}
}
std::string hall::getname() { return hallname; }
double hall::getticketprice() const { return ticketprice; }
hall::~hall() {
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			delete seats[row][column];
		}
	}
}
int hall::reserve(char c, int i) {
	if (seats[c - 'A'][i]->is_reserved() == false) {
		seats[c - 'A'][i]->reserve();
		return 1;
	}
	else {;return 0; }
}
void hall::displayavailableseats() {
	cout << "\t\t Available Seats \n";
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			if (seats[row][column]->is_reserved()) {
				cout << "   ";
			}
			else cout << seats[row][column]->getseatnum()<<" ";
		}
		cout << endl;
	}
}

