#include "VIPhall.h"
VIPhall::VIPhall() {
	ticketprice = 500;
	hallname = "VIP";

}
double VIPhall::getPrice() {
	return ticketprice;
}