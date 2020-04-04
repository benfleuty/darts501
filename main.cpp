#include <iostream>
#include <string>
#include <climits> // INT_MAX
#include <math.h>

#include "UserIO.h"
#include "Game.h"
#include "Player.h"

#define GET_SQUARE = pow(int,2)

typedef unsigned short ushort;
typedef unsigned int uint;

Player P1;
Player P2;

string msg;

//region PlayerSetup
void SetupP1() {
    P1.SetName(UserIO::String("Enter Player 1's name: "));
    UserIO::ClearScreen();
    do {
        P1.SetAccuracy(UserIO::uShort("Enter " + P1.GetName() + "'s accuracy [1-100]: "));
        if(P1.GetAccuracy() > 0 && P1.GetAccuracy() <= 100) break;
        cout << "\nInvalid accuracy!";
        UserIO::ClearScreen();
    }
    while (P1.GetAccuracy() == 0 || P1.GetAccuracy() > 100);
    P1.SetCPU(UserIO::Bool("Is " + P1.GetName() + " controlled by the computer? [Y/N]: "));
}

void SetupP2() {
    P2.SetName(UserIO::String("Enter Player 2's name: "));
    UserIO::ClearScreen();
    do {
        P2.SetAccuracy(UserIO::uShort("Enter " + P2.GetName() + "'s accuracy [1-100]: "));
        if(P2.GetAccuracy() > 0 && P2.GetAccuracy() <= 100) break;
        cout << "\nInvalid accuracy!";
        UserIO::ClearScreen();
    }
    while (P2.GetAccuracy() == 0 || P2.GetAccuracy() > 100);
    P2.SetCPU(UserIO::Bool("Is " + P2.GetName() + " controlled by the computer? [Y/N]: "));
}

bool CheckP1() {
    while (true) {
        UserIO::ClearScreen();
        string prompt = "Player 1:\nName: " + P1.GetName() +
                "\nAccuracy: " + to_string(P1.GetAccuracy()) +
                "\n" + ((P1.IsCPU()) ? "CPU" : "User" ) + " controlled"+
                "\nAre these details correct? [Y/N]:";
        return UserIO::Bool(prompt);

    }
}

bool CheckP2() {
    while (true) {
        UserIO::ClearScreen();
        string prompt = "Player 2:\nName: " + P2.GetName() +
                "\nAccuracy: " + to_string(P2.GetAccuracy()) +
                 "\n" + ((P2.IsCPU()) ? "CPU" : "User" ) + " controlled"+
                "\nAre these details correct? [Y/N]:";
        return UserIO::Bool(prompt);
    }
}

void CheckPlayers() {
    while (true)
    {
        bool P1Ready = CheckP1();
        UserIO::ClearScreen();
        if (!P1Ready) SetupP1();
        UserIO::ClearScreen();
        bool P2Ready = CheckP2();
        UserIO::ClearScreen();
        if (!P2Ready) SetupP2();

        if (P1Ready && P2Ready) return;
    }
}


ushort CalcThrowResult(ushort playerAccuracy){
    ushort accuracy = playerAccuracy;
    ushort randNum = rand() % 101;

    // hit
    if(randNum < accuracy) return 0;

    // miss
    return abs(randNum - accuracy);
    // range between randNum and accuracy is the distance from the bull
}

float sq(float value){
    return pow(value,2);
}

float getHyp(float x,float y, bool SQRT = true){
    if (SQRT) return sqrt(sq(x) + sq(y));
    return sq(x) + sq(y);
}

bool WhoThrowsFirst() {
    ushort p1X,p2X,p1Y,p2Y;
    float p1Result,p2Result;
    while(true){
        // halve results for midpoint of hyp
        p1X = CalcThrowResult(P1.GetAccuracy()) * 0.5;
        p1Y = CalcThrowResult(P1.GetAccuracy()) * 0.5;

        // get the length of the midpoint
        p1Result = getHyp(p1X,p1Y);
        
        p2X = CalcThrowResult(P2.GetAccuracy()) * 0.5;
        p2Y = CalcThrowResult(P2.GetAccuracy()) * 0.5;

        p2Result = getHyp(p2X,p2Y);

        if (p1Result < p2Result) return true;
        else if(p2Result < p1Result) return false;
    }
}
//endregion


//region SimulationSetup
uint GetIterations() {
    uint simulationIterations = 0;
    while (!simulationIterations) {
        string prompt = "\nEnter the number of iterations you want to run\n[Min: 1, Max: " + to_string(UINT_MAX) + "]: ";
        simulationIterations = UserIO::uInt(prompt);
    }
    return simulationIterations;
}

Game SetupGame() {
    UserIO::ClearScreen();
    bool firstThrower = WhoThrowsFirst();
    if (firstThrower) {
        msg = P1.GetName();
        cout << P1.GetName();
    }
    else {
        msg = P2.GetName();
        cout << P2.GetName();
    }

    cout << " landed closest to the bull and will throw first!\n";
    msg += " threw first on the first game\n";
    return Game(P1, P2, GetIterations(), firstThrower);
}

//endregion

int main() {
    srand(ulong(0)); // cast to ulong to stop warning C4244
    UserIO::ClearScreen();
#ifdef _WIN32
    system("title \"501 Darts | Ben Fleuty 1900040 | CMP 102 Assessment");
#endif

    SetupP1();

    UserIO::ClearScreen();

    SetupP2();

    UserIO::ClearScreen();

    CheckPlayers();

    UserIO::ClearScreen();

    Game game = SetupGame();

    game.Start();

    UserIO::ClearScreen();
    cout.clear();
    cout << msg << game.GetReport();

    return 0;
}
