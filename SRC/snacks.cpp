#include "snacks.h"
using namespace std;
#include<iostream>
int snacks::getQuantity() {
	return quantity;
}
float snacks::getPrice() {
	return price;
}
string snacks::getItemName() {
	return itemName;
}
void snacks::setprice(float f) {
	price = f;
}
void snacks::setitemName(string n) {
	itemName = n;
}
void snacks::setQuantity(int q) {
	quantity = q;
}
void snacks::supplySnack(int n) {
	quantity += n;
}
void snacks::buySnacks(int n) {
	quantity -= n;

}

