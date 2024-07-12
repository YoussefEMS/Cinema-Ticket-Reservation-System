using namespace std;
#pragma once
#include<iostream>
#include<string>
#include"Movie.h"
class Person
{
protected:
	string emails[100];
	string email, password;
	string* data = new string[100];
	string* data2 = new string[100];
	int counter = 0 , counter2= 0;
	char identity;
public:

	Person();
	string get_email();
	char  validate();
	char password_recheck(int);
	char password_recheck2(int);
	char registering();
	char get_identity();
	
	
	
};

