  #pragma once
#include <iostream>
class seat {
private:
	std::string seatnum;
	char row;
	int column;
	bool reserved;
public:
	bool is_reserved();
	seat(char='A', int=0);
	std::string getseatnum() const;
	seat& operator =(const seat&);
	char getrow() const;
	int getcolumn()const;
	void reserve();
	~seat();

};

