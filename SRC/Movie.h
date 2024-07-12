#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "VIPhall.h"
#include"Standardhall.h"
#include"KidsHall.h"
#include"hall.h"
using namespace std;

class Movie {
private:
    string title;
    string genre;
    string language;
    string directorName;
    double duration;
    double rating;
    int YearOfRelease;
   
public:
    hall*  h=0;
    Movie();
    Movie(const string& title, const string& genre, const string& language, const string& directorName, double duration, double rating, int );
    void setYearOfRelease(const int&);
    int  getYearOfRelease();
    bool setTitle(const string& title);
    void setGenre(const string& genre);
    void setLanguage(const string& language);
    void setDirectorName(const string& directorName);
    void setDuration(double duration);
    void setRating(double rating);
    //void setDateOfRelease(ScheduleStruct& dateOfRelease);

    const string& getTitle() const;
    const string& getGenre() const;
    const string& getLanguage() const;
    const string& getDirectorName() const;
    double getDuration() const;
    double getRating() const;
    void DisplayData() const;
    ~Movie();
    //ScheduleStruct getDateOfRelease() const;
};
