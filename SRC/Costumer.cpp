#include "Costumer.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

Costumer::Costumer(string e) : currentcheck(0), currentSessionReservationsCount(0) {
    email = e;
    readMoviesFromFile();
    checkAndUpdateTickets();
}
bool Costumer::ValidateMovie(string s) {
    for (int i = 0; i < readMoviesFromFile(); i++) {
        if (s == movies[i].getTitle()) { return true; }
    }
    return false;
}

int Costumer::readMoviesFromFile() {
    ifstream file("movies.txt");
    if (file.is_open()) {
        int count = 0;
        string title, genre, language, directorName;
        double duration, rating;
        int YearOfRelease;

        while (count < 5 && getline(file, title)) {
            getline(file, genre);
            getline(file, language);
            getline(file, directorName);
            file >> duration;
            file >> rating;
            file >> YearOfRelease;
            file.ignore();

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

void Costumer::Reserve_seat(string m, int n, string s) {
    int i;
    for (i = 0; i < readMoviesFromFile(); i++) {
        if (m == movies[i].getTitle()) break;
    }
    if (s == "VIP") {
        movies[i].h = new VIPhall;
    }
    else if (s == "KID") {
        movies[i].h = new KidsHall;
    }
    else if (s == "STD") {
        movies[i].h = new Standardhall;
    }

    readReservedSeats(m, s, movies[i].h);
    movies[i].h->displayavailableseats();
    char c;
    int k;
    for (int v = 0; v < n; v++) {
        cout << "Enter Seat Number, Letter from A-E and number from 0 to 9\n";
        cin >> c >> k;
        while (k > 9 || k < 0 || c < 'A' || c>'E') { cout << "Enter a valid seat number\n"; cin >> c >> k; }
        while (movies[i].h->reserve(c, k) != 1) {
            cout << "This seat is already taken, please choose another seat from A-E and 1-10\n";
            cin >> c >> k;
            while (k > 9 || k < 0 || c < 'A' || c>'E') { cout << "Enter a valid seat number\n"; cin >> c >> k; }
        }
        cout << "Seat " << c << k << " has been reserved.\n";
        updateHallFile(movies[i].getTitle(), s, c, k);
        writeTicketToFile(movies[i].h, c, k, movies[i].getTitle());
        currentcheck += movies[i].h->getticketprice();

        // Track the current session's reservations
        currentSessionReservations[currentSessionReservationsCount].setter(movies[i].getTitle(), s, c, k);
        currentSessionReservationsCount++;
    }
}
bool Costumer::displaymovieinfo(const string &title){
    for (int i = 0; i < readMoviesFromFile(); i++) {
        if (movies[i].getTitle() == title) {
            cout << "Movie: " << movies[i].getTitle();
            cout << "\nGenre: " << movies[i].getGenre();
            cout << "\nDirector Name: " << movies[i].getDirectorName();
            cout << "\nDuration: " << movies[i].getDuration();
            cout << "\nLanguage: " << movies[i].getLanguage();
            cout << "\nRating: " << movies[i].getRating()<<endl;
            cout << "Year Of Release: " << movies[i].getYearOfRelease() << endl;
            return true;
        }
    }
    return false;
}
int Costumer::getcurrentcheck() {
    return currentcheck;
}

void Costumer::displaymovies() {
    int c = readMoviesFromFile();
    for (int i = 0; i < c; i++) {
        cout << "Movie " << i + 1 << ": " << movies[i].getTitle() << endl;
    }
}
void Costumer::updateHallFile(const string movieTitle, const string& hallType, const char& seatRow, const int& seatNumber) {
    string fileName = "Movies/" + movieTitle + "/" + hallType + ".txt";
    ofstream file(fileName, ios::app); // Open the file in append mode
    if (file.is_open()) {
        file << seatRow << seatNumber << endl;
        file.close();
    }
    else {
        cout << "Unable to open file for writing.\n";
    }
}

void Costumer::writeTicketToFile(hall* h, char row, int col, string movie) {
    string fileName = "UserData/" + email + ".txt";
    ofstream file(fileName, ios::app);
    if (file.is_open()) {
        file << "Movie: " << movie << endl;
        file << "Seat: " << row << col << endl;
        file << "Price: " << h->getticketprice() << endl;
        file << "Hall: " << h->getname() << endl;
        file << endl;
        file.close();
    }
    else {
        cout << "Unable to open file for writing.\n";
    }
}

void Costumer::readReservedSeats(const string& movieTitle, const string& hallType, hall* h) {
    string fileName = "Movies/" + movieTitle + "/" + hallType + ".txt";
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                // Extract row and column from the line
                char row = line[0];
                int column = stoi(line.substr(1));
                // Reserve the seat in the hall object
                h->reserve(row, column);
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file for reading.\n";
    }
}
void Costumer::cancelReservation() {
    const int MAX_RESERVATIONS = 100;
    string fileName = "UserData/" + email + ".txt";
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file for reading.\n";
        return;
    }

    string lines[MAX_RESERVATIONS];
    int lineCount = 0;
    string line;
    while (getline(file, line) && lineCount < MAX_RESERVATIONS) {
        lines[lineCount++] = line;
    }
    file.close();

    // Display reservations to the user
    cout << "Your current reservations:\n";
    for (int i = 0; i < lineCount; i += 5) {
        cout << (i / 5 + 1) << ". " << lines[i] << " " << lines[i + 1] << " " << lines[i + 2] << " " << lines[i + 3] << endl;
    }

    cout << "Enter the number(s) of the reservation(s) you want to cancel, separated by space (end input with a non-number character):\n";
    int cancelIndices[MAX_RESERVATIONS / 5];
    int cancelCount = 0;
    int index;
    while (cin >> index) {
        if (index < 1 || index > lineCount / 5) {
            cout << "Invalid input. Try again:\n";
            continue;
        }
        cancelIndices[cancelCount++] = (index - 1) * 5;
    }
    cin.clear(); // Clear the error flag set by the non-number character
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the input

    // Remove canceled reservations from the file content
    for (int i = 0; i < cancelCount; ++i) {
        int cancelIndex = cancelIndices[i];
        string priceLine = lines[cancelIndex + 2].substr(7); // Extract price string
        currentcheck -= stof(priceLine); // Subtract price from current check
        for (int j = cancelIndex; j < lineCount - 5; ++j) {
            lines[j] = lines[j + 5];
        }
        lineCount -= 5;
    }

    // Write the updated reservations back to the file
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cout << "Unable to open file for writing.\n";
        return;
    }
    for (int i = 0; i < lineCount; ++i) {
        outFile << lines[i] << endl;
    }
    outFile.close();

    // Update the hall files to reflect the cancellations
    for (int i = 0; i < cancelCount; ++i) {
        int cancelIndex = cancelIndices[i];
        string movieTitle = lines[cancelIndex].substr(7);
        char seatRow = lines[cancelIndex + 1][6];
        int seatNumber = stoi(lines[cancelIndex + 1].substr(7));
        string hallType = lines[cancelIndex + 3].substr(6);

        string hallFileName = "Movies/" + movieTitle + "/" + hallType + ".txt";
        ifstream hallFile(hallFileName);
        if (!hallFile.is_open()) {
            continue;
        }

        string hallLines[MAX_RESERVATIONS];
        int hallLineCount = 0;
        while (getline(hallFile, line) && hallLineCount < MAX_RESERVATIONS) {
            hallLines[hallLineCount++] = line;
        }
        hallFile.close();

        ofstream hallOutFile(hallFileName);
        if (!hallOutFile.is_open()) {
            continue;
        }
        for (int j = 0; j < hallLineCount; ++j) {
            if (!(hallLines[j][0] == seatRow && stoi(hallLines[j].substr(1)) == seatNumber)) {
                hallOutFile << hallLines[j] << endl;
            }
        }
        hallOutFile.close();
    }

    cout << "The selected reservations have been canceled.\n";
}

void Costumer::cancelRecentReservations() {
    if (currentSessionReservationsCount == 0) {
        cout << "No recent reservations to cancel.\n";
        return;
    }

    cout << "Your recent reservations:\n";
    for (size_t i = 0; i < currentSessionReservationsCount; ++i) {
        const auto& res = currentSessionReservations[i];
        cout << (i + 1) << ". Movie: " << res.getmovietitle() << ", Hall: " << res.gethalltype() << ", Seat: " << res.getseatrow() << res.getcolumn() << endl;
    }

    cout << "Enter the number(s) of the reservation(s) you want to cancel, separated by space (end input with a non-number character):\n";
    const int MAX_RESERVATIONS = 100;
    int cancelIndices[MAX_RESERVATIONS / 5];
    int cancelCount = 0;
    int index;
    while (cin >> index) {
        if (index < 1 || index > currentSessionReservationsCount) {
            cout << "Invalid input. Try again:\n";
            continue;
        }
        cancelIndices[cancelCount++] = index - 1;
    }
    cin.clear(); // Clear the error flag set by the non-number character
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the input

    // Remove canceled reservations in reverse order from the end
    for (int i = cancelCount - 1; i >= 0; --i) {
        int cancelIndex = cancelIndices[i];
        const auto& res = currentSessionReservations[cancelIndex];

        // Update the user's file
        string fileName = "UserData/" + email + ".txt";
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Unable to open file for reading.\n";
            return;
        }

        string lines[MAX_RESERVATIONS];
        int lineCount = 0;
        string line;
        while (getline(file, line) && lineCount < MAX_RESERVATIONS) {
            lines[lineCount++] = line;
        }
        file.close();

        for (int j = 0; j < lineCount; ++j) {
            if (lines[j] == "Movie: " + res.getmovietitle()) {
                if (lines[j + 1] == "Seat: " + string(1, res.getseatrow()) + to_string(res.getcolumn())) {
                    string priceLine = lines[j + 2].substr(7);
                    currentcheck -= stof(priceLine); // Subtract price from current check
                    for (int k = j; k < lineCount - 5; ++k) {
                        lines[k] = lines[k + 5];
                    }
                    lineCount -= 5;
                }
            }
        }

        ofstream outFile(fileName);
        if (!outFile.is_open()) {
            cout << "Unable to open file for writing.\n";
            return;
        }
        for (int j = 0; j < lineCount; ++j) {
            outFile << lines[j] << endl;
        }
        outFile.close();

        // Update the hall file
        string hallFileName = "Movies/" + res.getmovietitle() + "/" + res.gethalltype() + ".txt";
        ifstream hallFile(hallFileName);
        if (!hallFile.is_open()) {
            continue;
        }

        string hallLines[MAX_RESERVATIONS];
        int hallLineCount = 0;
        while (getline(hallFile, line) && hallLineCount < MAX_RESERVATIONS) {
            hallLines[hallLineCount++] = line;
        }
        hallFile.close();

        ofstream hallOutFile(hallFileName);
        if (!hallOutFile.is_open()) {
            continue;
        }
        for (int j = 0; j < hallLineCount; ++j) {
            if (!(hallLines[j][0] == res.getseatrow() && stoi(hallLines[j].substr(1)) == res.getcolumn())) {
                hallOutFile << hallLines[j] << endl;
            }
        }
        hallOutFile.close();

        // Remove canceled reservation from the session list
        for (int j = cancelIndex; j < currentSessionReservationsCount - 1; ++j) {
            currentSessionReservations[j] = currentSessionReservations[j + 1];
        }
        currentSessionReservationsCount--;
    }

    cout << "The selected recent reservations have been canceled.\n";
}




void Costumer::buySnacks() {
    readSnacks();
    float sum = 0;
    bool flag = false;
    string s;
    int q;
    cout << "Available snacks:\n";
    for (int i = 0; i < numberOfSnacks; i++) {
        cout << snack[i].getItemName() << " - " << snack[i].getPrice() << " EGP (Available: " << snack[i].getQuantity() << ")\n";
    }
    cout << "What item do you want to buy? ";
    cin >> s;
    for (int i = 0; i < numberOfSnacks; i++) {
        if (s == snack[i].getItemName()) {
            if (snack[i].getQuantity() > 0) {
                cout << "How many " << s << " items do you want to buy? ";
                cin >> q;
                if (snack[i].getQuantity() >= q) {
                    snack[i].buySnacks(q);
                    flag = true;
                    sum += q * snack[i].getPrice();
                    cout << "Your checkout: " << sum << " Pounds\n";
                }
                else {
                    cout << "Sorry, only " << snack[i].getQuantity() << " items of " << s << " are available.\n";
                }
            }
            else {
                cout << "Sorry, " << s << " is out of stock at the moment.\n";
            }
            break;
        }
    }
    if (!flag) {
        cout << "Item not found.\n";
    }

    if (flag) {
        currentcheck += sum;
        ofstream outFile("snacks_temp.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < numberOfSnacks; i++) {
                outFile << snack[i].getItemName() << endl;
                outFile << snack[i].getQuantity() << endl;
                outFile << snack[i].getPrice() << endl;
            }
            outFile.close();
            remove("snacks.txt");
            rename("snacks_temp.txt", "snacks.txt");
        }
        else {
            cout << "Unable to open file for writing.\n";
        }
    }
}

void Costumer::readSnacks() {
    string line;
    ifstream file("snacks.txt");
    if (file.is_open()) {
        for (int i = 0; i < numberOfSnacks; i++) {
            if (getline(file, line)) {
                snack[i].setitemName(line);
            }
            if (getline(file, line)) {
                snack[i].setQuantity(stoi(line));
            }
            if (getline(file, line)) {
                snack[i].setprice(stof(line));
            }
        }
        file.close();
    }
}
void Costumer::checkAndUpdateTickets() {
    string userFile = "UserData/" + email + ".txt";
    ifstream file(userFile);
    if (!file.is_open()) {
        cout << "Unable to open user file.\n";
        return;
    }

    string lines[100];
    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        lines[lineCount++] = line;
    }
    file.close();

    ofstream outFile(userFile);
    if (!outFile.is_open()) {
        cout << "Unable to open user file for writing.\n";
        return;
    }

    for (int i = 0; i < lineCount; i += 5) {
        if (ValidateMovie(lines[i].substr(7))) { // "Movie: " is 7 characters
            for (int j = 0; j < 5; j++) {
                outFile << lines[i + j] << endl;
            }
        }
    }
    outFile.close();
}

Costumer::~Costumer() {}
