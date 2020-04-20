#include <iostream>
#include <string>
#include <climits> // INT_MAX
#include <cmath>
#include <ctime>

#include "UserIO.h"
#include "Game.h"
#include "Player.h"

typedef unsigned short ushort;
typedef unsigned int uint;

Player P1;
Player P2;

string msg;

//region PlayerSetup
void SetupPlayer(Player &player) {
    bool ready;
    do {
        player.SetName(UserIO::String("Enter a player's name: "));
        UserIO::ClearScreen();
        do {
            player.SetAccuracy(UserIO::uShort("Enter " + player.GetName() + "'s accuracy [1-100]: "));
            if (player.GetAccuracy() > 0 && player.GetAccuracy() <= 100) break;
            cout << "\nInvalid accuracy!";
            UserIO::ClearScreen();
        } while (player.GetAccuracy() == 0 || player.GetAccuracy() > 100);
        player.SetCPU(UserIO::Bool("Is " + player.GetName() + " controlled by the computer? [Y/N]: "));
        UserIO::ClearScreen();
        string prompt = // region prompt
                "Player 1:\nName: " + player.GetName() +
                "\nAccuracy: " + to_string(player.GetAccuracy()) +
                "\n" + ((player.IsCPU()) ? "CPU" : "User") + " controlled" +
                "\nAre these details correct? [Y/N]:";
                        //endregion
        ready = UserIO::Bool(prompt);
    } while (!ready);
}


ushort CalcThrowResult(ushort playerAccuracy) {
    ushort accuracy = playerAccuracy;
    ushort randNum = rand() % 101;

    // hit
    if (randNum < accuracy) return 0;

    // miss
    return abs(randNum - accuracy);
    // range between randNum and accuracy is the distance from the bull
}

float sq(float value) {
    return pow(value, 2);
}

float getHyp(float x, float y, bool SQRT = true) {
    if (SQRT) return sqrt(sq(x) + sq(y));
    return sq(x) + sq(y);
}

bool WhoThrowsFirst() {
    ushort p1X, p2X, p1Y, p2Y;
    float p1Result, p2Result;
    while (true) {
        // halve results for midpoint of hyp
        p1X = CalcThrowResult(P1.GetAccuracy()) * 0.5;
        p1Y = CalcThrowResult(P1.GetAccuracy()) * 0.5;

        // get the length of the midpoint
        p1Result = getHyp(p1X, p1Y);

        p2X = CalcThrowResult(P2.GetAccuracy()) * 0.5;
        p2Y = CalcThrowResult(P2.GetAccuracy()) * 0.5;

        p2Result = getHyp(p2X, p2Y);

        if (p1Result < p2Result) return true;
        else if (p2Result < p1Result) return false;
    }
}
//endregion


//region SimulationSetup
uint GetIterations() {
    uint simulationIterations = 0;
    while (!simulationIterations) {
        string prompt =
                "\nEnter the number of iterations you want to run\n[Min: 1, Max: " + to_string(UINT_MAX) + "]: ";
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
    } else {
        msg = P2.GetName();
        cout << P2.GetName();
    }

    cout << " landed closest to the bull and will throw first!\n";
    msg += " threw first on the first game\n";

    bool aiAdvanced = false;
    if(P1.IsCPU() || P2.IsCPU())
        aiAdvanced = UserIO::Bool("Do you want the AI to be [s]imple or [a]dvanced: ",'s','a');
    return Game(P1, P2, GetIterations(), firstThrower,aiAdvanced);
}

//endregion

int main() {
    srand(time(0));
    UserIO::ClearScreen();
#ifdef _WIN32
    system("title \"501 Darts | Ben Fleuty 1900040 | CMP 102 Assessment");
#endif

#ifndef DEBUG
    SetupPlayer(P1);

    UserIO::ClearScreen();

    SetupPlayer(P2);

    UserIO::ClearScreen();

    Game game = SetupGame();

    game.Start();
#else
    UserIO::ClearScreen();
    enum Player {
        User, CPU
    };
    P1.SetName("ben");
    P1.SetAccuracy(73);
    P1.SetCPU(CPU);

    P2.SetName("neb");
    P2.SetAccuracy(71);
    P2.SetCPU(CPU);

    Game game = Game(P1, P2, 100, 0);
    game.Start();

#endif

    UserIO::ClearScreen();
    cout.clear();
    cout << "Generating report...\n";
    string report = game.GetReport();
    UserIO::ClearScreen();
    cout << msg << report;

    return 0;
}
