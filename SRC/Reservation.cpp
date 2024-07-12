#include "Reservation.h"
#include "seat.h"

void Reservation::setter(string movie, string hall, char row, int col) 
{
	movietitle = movie;
	halltype = hall;
	seatrow = row;
	seatcolumn = col;
}
string Reservation::getmovietitle() const { return movietitle; }
string Reservation::gethalltype() const { return halltype; }
char Reservation::getseatrow() const { return seatrow; }
int Reservation::getcolumn() const { return seatcolumn; }