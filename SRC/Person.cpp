#include "Person.h"
#include <iostream>
#include <fstream>
#include<string>
using namespace std;

Person::Person() {}
string Person::get_email() {
    return email;
}

char Person::password_recheck(int c) {
    cout << "Incorrect Password\nTry again!!!\n";
    for (int i = 0; i <= 2; i++) {
        cout << "Enter Your Password: \n";
        cin >> password;
        if (data[c + 1] == password) {
            cout<<"Correct Email and Password\n";
            cout << "Welcome Costumer\n";
            identity = 'C';
            return 'C';
        }
        else {
            cout << "Incorrect password\n";
            cout << "You have " << 2 - i << " trials left\n";
        }
    }
    return 0;
}
char Person::password_recheck2(int c) {
    cout << "Incorrect Password\nTry again!!!\n";
    for (int i = 0; i <= 2; i++) {
        cout << "Enter Your Password: \n";
        cin >> password;
        if (data2[c + 1] == password) {
            cout << "Correct Email and Password\n";
            cout << "Welcome Admin\n";
            identity = 'A';
            return 'A';
        }
        else {
            cout << "Incorrect password\n";
            cout << "You have " << 2 - i << " trials left\n";
        }
    }
    return 0;
}

char Person::validate() {
    cout << "Enter Your Email: \n";
    cin >> email;
    cout << "Enter Your Password: \n";
    cin >> password;
    ifstream file("users.txt");
    ifstream file2("Admin.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            data[counter] = line;
            counter++;
        }
        file.close();
    }
    if (file2.is_open()) {
        string line2;
        while (getline(file2, line2)) {
            data2[counter2] = line2;
            counter2++;
        }
        file.close();
    }
    int c;
    if (counter > counter2) {
        c = counter;
    }
    else { c = counter2; }
    for (int i = 0; i < c ; i += 2) {
        if (data[i] == email) {
            if (data[i + 1] == password) {
                cout << "Correct Email and Password\n";
                cout << "Welcome my dear Costumer\n";
                identity = 'C';
                return 'C';
            }
            else {
                return password_recheck(i);
            }
        }
        else if (data2[i] == email) {
            if (data2[i + 1] == password) {
                cout << "Correct Email and Password\n";
                cout << "Welcome Admin\n";
                identity = 'A';
                return 'A';
            }
            else {
                return password_recheck2(i);
            }
        }
    }
    return 0;
}

char Person::registering() {
    ifstream readFile("users.txt");
    ofstream writeFile("users.txt", ios::app);
    string existingEmail, existingPassword;

    if (!readFile.is_open() || !writeFile.is_open()) {
        cout << "Unable to open file.\n";
        return 'C';
    }

    cout << "\t\t\t\t\t\tRegister Page\n";

    while (true) {
        bool emailTaken = false;
        cout << "Enter Your email: \n";
        cin >> email;

        // Check if the email is already taken
        while (getline(readFile, existingEmail) && getline(readFile, existingPassword)) {
            if (existingEmail == email) {
                emailTaken = true;
                break;
            }
        }

        if (emailTaken) {
            cout << "Email is already taken, please enter another email.\n";
            readFile.clear(); // Clear the EOF flag
            readFile.seekg(0, ios::beg); // Rewind the file to the beginning
        }
        else {
            break; // Email is not taken, exit the loop
        }
    }

    cout << "Enter Your Password: \n";
    cin >> password;
    writeFile << email << endl;
    writeFile << password << endl;

    readFile.close();
    writeFile.close();

    return 'C';
}
char Person:: get_identity(){
    return identity;
}




    
        
