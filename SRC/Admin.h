#pragma once
#include "Person.h"
#include "Movie.h"
#include <string>
#include <iostream>
#include <fstream>
#include "snacks.h"

class Admin : public Person {
private:
    static const int MAX_MOVIES = 5;
    Movie movies[MAX_MOVIES];
    static const int numberOfSnacks = 3;
    snacks snack[numberOfSnacks];
    int count;

public:
    Admin();
    void addMovie();
    void deleteMovie();
    void writeMoviesToFile();
    int readMoviesFromFile();
    void adminMenu();
    void createMovieFolders(const string&);
    void supplySnacks();
    void readsnacks();
    void displaySnacks();
    void displaymovies();
};
void deleteDirectory(const string&);
bool isNumeric(const string&);

