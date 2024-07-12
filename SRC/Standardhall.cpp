#include "Standardhall.h"
Standardhall::Standardhall() {
	hallname = "STD";
	ticketprice = 150;
}
double Standardhall::getPrice() {
	return ticketprice;
}
