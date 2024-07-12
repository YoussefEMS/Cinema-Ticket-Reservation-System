#include "Movie.h"


Movie::Movie() : duration(0.0), rating(0.0) {}


Movie::Movie(const string& title, const string& genre, const string& language, const string& directorName, double duration, double rating, int YearOfRelease)
    : title(title), genre(genre), language(language), directorName(directorName), duration(duration), rating(rating), YearOfRelease(YearOfRelease) {}


bool Movie::setTitle(const string& title)
{
    this->title = title;
    return true;
}
void Movie::setYearOfRelease(const int& YearOfRelease) { this->YearOfRelease=YearOfRelease; }
int Movie::getYearOfRelease() { return YearOfRelease; }
void Movie::setGenre(const string& genre)
{
    this->genre = genre;
}

void Movie::setLanguage(const string& language)
{
    this->language = language;
}

void Movie::setDirectorName(const string& directorName)
{
    this->directorName = directorName;
}

void Movie::setDuration(double duration)
{
    this->duration = duration;
}

void Movie::setRating(double rating)
{
    this->rating = rating;
}

//void Movie::setDateOfRelease(ScheduleStruct& dateOfRelease)

 //   this->dateOfRelease = dateOfRelease;


const string& Movie::getTitle() const
{
    return title;
}

const string& Movie::getGenre() const
{
    return genre;
}

const string& Movie::getLanguage() const
{
    return language;
}

const string& Movie::getDirectorName() const
{
    return directorName;
}

double Movie::getDuration() const
{
    return duration;
}

double Movie::getRating() const
{
    return rating;
}
void Movie::DisplayData() const {
    cout << "Movie Name: " << title << endl;
    cout << "Genre: " << genre << endl;
    cout << "Language: " << language << endl;
    cout << "Director: " << directorName << endl;
    cout << "Duration: " << duration << endl;
    cout << "Rating: " << rating << endl;
}
Movie::~Movie() { delete h; }