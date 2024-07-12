#ifndef snacks_HEADER
#define snacks_HEADER
#include<iostream>
using namespace std;

class snacks {
private:
	int quantity;
	float price;
	string itemName;
public:
	int getQuantity();
	float getPrice();
	string getItemName();
	void setprice(float);
	void setQuantity(int);
	void setitemName(string);
	void supplySnack(int);
	void buySnacks(int);
};
#endif

