#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdio>
#include <cctype>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <direct.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif
using namespace std;
Admin::Admin() : count(0) {
    adminMenu();
    readMoviesFromFile();
}
void Admin::adminMenu() {
    char choice;
    do {
        cout << "Admin Menu:\n";
        cout << "(a) Add Movie\n";
        cout << "(d) Delete Movie\n";
        cout << "(s) Supply Snacks\n";
        cout << "(q) Quit\n";

        // Validate input
        while (true) {
            string input;
            cout << "Enter your choice: ";
            cin >> input;
            if (input.length() == 1) {
                choice = input[0];
                break;
            }
            else {
                cout << "Invalid input. Please enter a single character.\n";
            }
        }

        switch (choice) {
        case 'a':
            addMovie();
            break;
        case 'd':
            deleteMovie();
            break;
        case 'q':
            cout << "Exiting Admin Menu\n";
            break;
        case 's':
            supplySnacks();
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 'q');
}

void Admin::addMovie() {
    if (count >= MAX_MOVIES) {
        cout << "Movie list is full!" << endl;
        return;
    }

    string title, genre, language, directorName;
    double duration, rating;
    string test;
    int YearOfRelease;
    cin.ignore(); // Clear newline character left in the input buffer
    cout << "Enter movie title: ";
    getline(cin, title);
    cout << "Enter movie genre: ";
    getline(cin, genre);
    cout << "Enter movie language: ";
    getline(cin, language);
    cout << "Enter director name: ";
    getline(cin, directorName);
    cout << "Enter movie duration (in hours): ";
    cin >> test;
    while (!isNumeric(test) ||stod(test)>5 || stod(test)<1) { cout << "Please Enter a number 1-5 for the duration\n"; cin >> test; }
    duration = stod(test);;
    cout << "Enter movie rating (out of 10): ";
    cin >> test;
    while (!isNumeric(test) || stod(test)>10 || stod(test)<0) { cout << "Please Enter a number 0-10 for the rating\n"; cin >> test; }
    rating = stod(test);;
    cout << "Enter Year Of Release: ";
    cin >> test;
    while (!isNumeric(test) || stoi(test) > 2024 || stoi(test) < 1900) {
        cout << "Please Enter a number 1900-2024 for the year of release\n"; cin >> test;
    }
    YearOfRelease = stoi(test);
    cin.ignore(); // Clear newline character left in the input buffer

    movies[count].setTitle(title);
    movies[count].setGenre(genre);
    movies[count].setLanguage(language);
    movies[count].setDirectorName(directorName);
    movies[count].setDuration(duration);
    movies[count].setRating(rating);
    movies[count].setYearOfRelease(YearOfRelease);
    count++;

    // Open the file in append mode and write the new movie
    ofstream file("movies.txt", ios::app);
    if (file.is_open()) {
        file << title << endl;
        file << genre << endl;
        file << language << endl;
        file << directorName << endl;
        file << duration << endl;
        file << rating << endl;
        file << YearOfRelease << endl;
        file.close();
    }
    else {
        cout << "Unable to open file for writing.\n";
    }

    createMovieFolders(title);
    cout << "Movie added" << endl;
}


void Admin::writeMoviesToFile() {
    ofstream file("movies_temp.txt");
    if (file.is_open()) {
        for (int i = 0; i < count; i++) {
            file << movies[i].getTitle() << endl;
            file << movies[i].getGenre() << endl;
            file << movies[i].getLanguage() << endl;
            file << movies[i].getDirectorName() << endl;
            file << movies[i].getDuration() << endl;
            file << movies[i].getRating() << endl;
            file << movies[i].getYearOfRelease() << endl;
        }
        file.close();
        remove("movies.txt");
        rename("movies_temp.txt", "movies.txt");
    }
    else {
        cout << "Unable to open file for writing.\n";
    }
}


int Admin::readMoviesFromFile() {
    ifstream file("movies.txt");
    if (file.is_open()) {
        count = 0;
        string title, genre, language, directorName;
        double duration, rating;
        int YearOfRelease;

        while (count < MAX_MOVIES && getline(file, title)) {
            getline(file, genre);
            getline(file, language);
            getline(file, directorName);
            file >> duration;
            file >> rating;
            file >> YearOfRelease;
            file.ignore(); // Ignore the newline character after the rating

            movies[count].setTitle(title);
            movies[count].setGenre(genre);
            movies[count].setLanguage(language);
            movies[count].setDirectorName(directorName);
            movies[count].setDuration(duration);
            movies[count].setRating(rating);
            movies[count].setYearOfRelease(YearOfRelease);
            count++;
        }
        file.close();
        return count;
    }
    else {
        cout << "Unable to open file for reading.\n";
        return 0;
    }
}


void Admin::deleteMovie() {
    string title;
    displaymovies();
    cout << "Enter the title of the movie to delete: ";
    cin.ignore(); // Clear newline character left in the input buffer
    getline(cin, title);

    int c = readMoviesFromFile();
    ofstream outFile("movies_temp.txt");
    if (outFile.is_open()) {
        bool found = false;
        for (int i = 0; i < c; i++) {
            if (movies[i].getTitle() != title) {
                outFile << movies[i].getTitle() << endl;
                outFile << movies[i].getGenre() << endl;
                outFile << movies[i].getLanguage() << endl;
                outFile << movies[i].getDirectorName() << endl;
                outFile << movies[i].getDuration() << endl;
                outFile << movies[i].getRating() << endl;
                outFile << movies[i].getYearOfRelease() << endl;
            }
            else {
                found = true;
            }
        }
        outFile.close();
        if (found) {
            string movieDir = "Movies/" + title;
            deleteDirectory(movieDir);
            remove("movies.txt");
            rename("movies_temp.txt", "movies.txt");
            cout << "Movie deleted successfully." << endl;
        }
        else {
            remove("movies_temp.txt");
            cout << "Movie not found." << endl;
        }
    }
    else {
        cout << "Unable to open file for writing.\n";
    }
}

void Admin::readsnacks() {
    string line;
    int quantity;
    string name;
    float price;
    ifstream file("snacks.txt");
    if (file.is_open()) {
        for (int i = 0; i < numberOfSnacks; i++) {
            if (getline(file ,line)){ snack[i].setitemName(line); }
            if(getline(file, line)){ snack[i].setQuantity(stoi(line)); }
            if (getline(file, line)) {
                snack[i].setprice(stof(line));
            }
            
        }


        file.close();
    }
}
void Admin::supplySnacks() {
    readsnacks();
    displaySnacks();
    bool flag = false;
    string s;
    int q;
    cout << "Which snack you want to supply: ";
    cin >> s;
    for (int i = 0; i < numberOfSnacks; i++) {
        if (s == snack[i].getItemName()) {
            cout << "Enter the number of units to be supplied for the chosen snack: ";
            cin >> q;
            snack[i].supplySnack(q);
            flag = true;
        }
    }
    if (flag == false) {
        cout << "Item not found\n";

    }
    ofstream outFile("snacks_temp.txt");
    if (outFile.is_open() && flag == true) {
        for (int i = 0; i < numberOfSnacks; i++) {

            outFile << snack[i].getItemName() << endl;
            outFile << snack[i].getQuantity() << endl;
            outFile << snack[i].getPrice() << endl;
        }
        outFile.close();
        remove("snacks.txt");
        rename("snacks_temp.txt", "snacks.txt");
        cout << "Item supplied\n";


    }
}
void Admin::displaySnacks() {
    readsnacks();
    cout << "Available snacks:\n";
    for (int i = 0; i < numberOfSnacks; i++) {
        cout << snack[i].getItemName() << " - " << snack[i].getPrice() << " EGP (Available: " << snack[i].getQuantity() << ")\n";
    }
}
void createDirectory(const string& path) {
#if defined(_WIN32) || defined(_WIN64)
    _mkdir(path.c_str());
#else
    mkdir(path.c_str(), 0777);
#endif
}

void createFile(const string& path, const string& content) {
    ofstream file(path);
    if (file.is_open()) {
        file << "A0" << endl;
        file.close();
    }
    else {
        cout << "Unable to create file: " << path << endl;
    }
}
void Admin::createMovieFolders(const string& movieName) {
    string baseDir = "Movies/" + movieName;

    // Create base directory for the movie
    createDirectory(baseDir);

    // Schedule folders
    // Hall names
    string hallNames[3] = { "VIP", "STD", "KID" };

        for (const auto& hall : hallNames) {
            string filePath = baseDir + "/" + hall + ".txt";
            createFile(filePath, hall);

        }
}
void Admin::displaymovies() {
    int c = readMoviesFromFile();
    for (int i = 0; i < c; i++) {
        cout << "Movie " << i + 1 << ": " << movies[i].getTitle() << endl;
    }
}
bool isNumeric(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
void deleteDirectory(const string& path) {
#ifdef _WIN32
    string command = "rmdir /s /q \"" + path + "\""; // Windows command to delete directory
    system(command.c_str());
#else
    string command = "rm -rf \"" + path + "\""; // Unix command to delete directory
    system(command.c_str());
#endif
}
