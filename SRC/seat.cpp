#include "seat.h"
#include <string>
seat::seat(char r, int c) {
	row = r;
	column = c;
	seatnum = std::string(1, row) + std::to_string(column);
	reserved = false;
}
std::string seat::getseatnum() const { return seatnum; }
seat& seat::operator=(const seat& s) {
	row = s.getrow();
	column = s.getcolumn();
	seatnum = s.getseatnum();
	return *this;
}
seat::~seat(){}
char seat::getrow() const { return row; }
int seat::getcolumn() const { return column; }
bool seat::is_reserved() {
	return reserved;
}
void seat::reserve() {
	reserved = true;
}