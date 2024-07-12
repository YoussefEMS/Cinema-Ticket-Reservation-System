#include <iostream>
#include <fstream>
#include "Person.h"
#include <string>
#include "Costumer.h"
#include "Admin.h"
#include <cstdlib>
#include <windows.h>
using namespace std;

void displayMainMenu();
void handleLogin(Person& obj, char& userType);
void handleRegister(Person& obj, char& userType);
void handleAdminMenu();
void handleCustomerMenu(Costumer& c);

int main() {
    Person obj;
    char mainChoice, userType = '.', subChoice;

    do {
        displayMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
        case 'l':
            handleLogin(obj, userType);
            break;
        case 'r':
            handleRegister(obj, userType);
            break;
        case 'q':
            exit(EXIT_SUCCESS);
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        if (userType == 'A') {
            handleAdminMenu();
        }
        else if (userType == 'C') {
            Costumer customer(obj.get_email());
            handleCustomerMenu(customer);
        }

    } while (mainChoice != 'q');

    return 0;
}

void displayMainMenu() {
    cout << "\t\t\t\t\t\tLogin page\t\t\t\n";
    cout << "(l) to Login (r) to Register (q) to Quit\n";
}

void handleLogin(Person& obj, char& userType) {
    userType = obj.validate();
    if (userType == 'A') {
        //cout << "Admin logged in.\n";
    }
    else if (userType == 'C') {
       // cout << "Customer logged in.\n";
    }
    else {
        cout << "Login failed.\n";
    }
}

void handleRegister(Person& obj, char& userType) {
    userType = obj.registering();
    if (userType == 'C') {
        cout << "Registration successful.\n";
    }
    else {
        cout << "Registration failed.\n";
    }
}

void handleAdminMenu() {
    Admin admin;
}

void handleCustomerMenu(Costumer& c) {
    char choice;
    string movie, hall, voucher;
    int number;

    do {
        cout << "Choose (r) to Reserve Seat/s, (c) to Cancel Reservation/s, (b) to Buy Snacks, (x) to Cancel Recent Reservation, (q) to Quit\n";
        cin >> choice;

        switch (choice) {
        case 'r':
            c.displaymovies();
            char choice7;
            cout << "Do you want more information about a specific movie? (y/n): ";
            cin >> choice7;

            if (choice7 == 'y' || choice7 == 'Y') {
                string selectedMovie;
                cout << "Enter the title of the movie you want more information about: ";
                cin >> selectedMovie;
                while (!c.displaymovieinfo(selectedMovie)) { cout << "Enter a valid Movie title: "; cin >> selectedMovie; }
            }
            cout << "Movie: ";
            cin >> movie;
            while (!c.ValidateMovie(movie)) { cout << "Please Enter a Valid Movie Name\n"; cin >> movie; }
            cout << "Standard hall(STD), KidsHall(KID), VIPHall(VIP): ";
            cin >> hall;
            while (hall != "VIP" && hall != "STD" && hall != "KID") { cout << "Please Enter a valid hall type: \n"; cin >> hall; }
            cout << "Number of tickets you want to reserve: ";
            cin >> number;
            while (number > 10) { cout << "You can't reserve more than 10 tickets, Please enter a smaller number: \n"; cin >> number; }
            c.Reserve_seat(movie, number, hall);
            cout << "You have successfully reserved the seats.\n";
            break;
        case 'c':
            c.cancelReservation();
            break;
        case 'x':
            c.cancelRecentReservations();
            break;
        case 'b':
            c.buySnacks();
            break;
        case 'q':
            if(c.getcurrentcheck()> 0 ){
            cout << "Final Price: " << c.getcurrentcheck() << " EGP\n";
            cout << "Proceed to checkout (k) or Enter Voucher code (e)\n";
            cin >> choice;
            if (choice == 'e') {
                cout << "Enter Voucher Code: ";
                cin >> voucher;
                if (voucher == "MOSALAH") {
                    cout << "New Final Price is " << c.getcurrentcheck() / 2 << " EGP\n";
                    exit(EXIT_SUCCESS);
                }
                else if (voucher == "DRCHERRY") {
                    cout << "New Final Price is 0 EGP\n" << "Dr. Cherry's blessings!\n";
                    exit(EXIT_SUCCESS);
                }
                else {
                    cout << "Invalid Voucher code.\n";
                }
            }

            }
            else if (choice == 'k') {
                exit(EXIT_SUCCESS);
            }
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 'q');
}
