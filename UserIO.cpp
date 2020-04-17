//
// Created by ben on 27/03/2020.
//

#include <string>
#include <iostream>

#include "UserIO.h"

using namespace std;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

void UserIO::ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
    system("echo 501 Darts - Ben Fleuty 1900040 - CMP 102 Assessment && echo");
#endif

}

void UserIO::ResetCin() {
    cin.clear();
    //cin.ignore();
}

string UserIO::String(const string &prompt = "", bool allowEmpty = false) {
    string userInput;
    cout << prompt;

    while (true) {
        //ResetCin();
        getline(cin, userInput);
        if (userInput.empty() || userInput[0] == ' ' && !allowEmpty) {
            ClearScreen();
            cout << "\nYour input was not a valid string!\n";
            if (prompt.empty()) cout << "Your input: ";
            else cout << prompt;
        } else break;
    }
    ResetCin();
    return userInput;
}

string UserIO::String(const string &prompt = "") {
    return String(prompt, false);
}

int UserIO::Int(const string &prompt) {
    string userInput;
    long int input;
    cout << prompt;

    while (true) {
        ResetCin();
        getline(cin, userInput);
        try {
            input = stoi(userInput);
            ResetCin();
            if (input > INT32_MAX)
                return INT32_MAX;

            return input;
        }
        catch (...) {
            cout << "\nYour input is not a valid number!\n";

            if (prompt.empty()) cout << "Your input: ";
            else cout << prompt;
        }
    }
}

uint UserIO::uInt(const string &prompt) {
    string userInput;
    unsigned long int input;
    cout << prompt;

    while (true) {
        ResetCin();
        getline(cin, userInput);
        try {
            input = stoi(userInput);
            ResetCin();
            if (input > UINT32_MAX)
                return UINT32_MAX;

            return input;
        }
        catch (...) {
            cout << "\nYour input is not a valid number!\n";

            if (prompt.empty()) cout << "Your input: ";
            else cout << prompt;
        }
    }
}

short UserIO::Short(const string &prompt) {
    string userInput;
    int input;
    cout << prompt;

    while (true) {
        ResetCin();
        getline(cin, userInput);
        try {
            input = stoi(userInput);
            ResetCin();
            if (input > INT16_MAX)
                return INT16_MAX;
            else if (input < INT16_MIN)
                return INT16_MIN;

            return input;
        }
        catch (...) {
            cout << "\nYour input is not a valid number!\n";
            if (prompt.empty()) cout << "Your input: ";
            else cout << prompt;
        }
    }
}

ushort UserIO::uShort(const string &prompt) {
    string userInput;
    uint input;
    cout << prompt;

    while (true) {
        ResetCin();
        getline(cin, userInput);

        try {
            input = stoul(userInput);
            ResetCin();
            if (input > UINT16_MAX)
                return UINT16_MAX;

            return input;
        }
        catch (...) {
            cout << "\nYour input is not valid!\n";

            if (prompt.empty()) cout << "Your input: ";
            else cout << prompt;
        }
    }
}

bool UserIO::Bool(const string& prompt) {
    while (true) {
        ClearScreen();
        unsigned char userInput = tolower(UserIO::String(prompt, false)[0]);
        if (userInput == 'n')
            return false;

        if (userInput == 'y')
            return true;
    }
}

bool UserIO::Bool(const string& prompt, char noChar = 'n', char yesChar = 'y') {
    while (true) {
        ClearScreen();
        unsigned char userInput = tolower(UserIO::String(prompt, false)[0]);
        if (userInput == noChar)
            return false;

        if (userInput == yesChar)
            return true;
    }
}

