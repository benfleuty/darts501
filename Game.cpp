//
// Created by ben on 27/03/2020.
//
#include <array>
#include <iostream>
#include <string>

#include "Game.h"
#include "UserIO.h"

using namespace std;
typedef unsigned short ushort;
typedef unsigned long ulong;

enum Multiplier {
    Zero, Single, Double, Triple
};

bool Game::IsSimulation(Player player1, Player player2) {
    return player1.IsCPU() && player2.IsCPU();
}

bool Game::IsPlayerVsAI() {
    return (_player1.IsCPU() ^ _player2.IsCPU());
}

void Game::GameClearScreen() {
    UserIO::ClearScreen();
    string out;
    Player player = _player1;
    for (int i = 0; i < 2; ++i) {
        out += player.GetName() + ":\n";
        out += "Score: " + to_string(player.GetScore());
        out += +"\nLast hit: ";
        if (player.GetLastTarget().GetMultiplier() > 0 && player.GetScore() < 501) {
            switch (player.GetLastTarget().GetMultiplier()) {
                case Single:
                    out += "single ";
                    break;
                case Double:
                    out += "double ";
                    break;
                case Triple:
                    out += "triple ";
                    break;
                default:
                    out += "ERROR";
                    break;
            }
            out += to_string(player.GetLastTarget().GetValue());
        } else out += "no darts thrown yet!";
        if (player.GetLastTarget().GetValue() > 1)
            out += " totalling " + to_string(player.GetLastTarget().GetValue(true));

        out += "\n";

        if (player.GetName() == _player2.GetName())
            out += "\n";
        else player = _player2;
    }

    cout << out << endl;
}


void Game::Start() {
    // Simulation Match loop
    if (IsSimulation(_player1, _player2)) {
        for (int i = 0; i < _iterations; ++i) {
            cout << "Game " << i + 1 << "\r";
            SimulateMatch();
        }
    }
        // Play Match loop
    else for (int i = 0; i < _iterations; ++i) PlayMatch();
}

void Game::SimulateMatch() {
    for (ushort i = 0; i < 13; ++i) {
        SimulateSet();
        if (p1SetWins == 7 || p2SetWins == 7) {
            array<ushort, 2> result = {p1SetWins, p2SetWins};
            _matches.push_back(result);
            p1SetWins = 0;
            p2SetWins = 0;
            break;
        }
    }
}

void Game::SimulateSet() {
    // Set loop
    for (int i = 0; i < 5; ++i) {
        SimulateGame();
        if (p1GameWins == 3 || p2GameWins == 3) {
            (p1GameWins == 3) ? p1SetWins++ : p2SetWins++;
            p1GameWins = 0;
            p2GameWins = 0;
            break;
        }
    }
}

void Game::SimulateGame() {
    // Game loop
    Player currentPlayer;
    _player1.Reset();
    _player2.Reset();
    if (_firstThrower) currentPlayer = _player1;
    else currentPlayer = _player2;
    _firstThrower = !_firstThrower;
    while (true) {
        currentPlayer = SimulateTurn(currentPlayer);
        if (currentPlayer.GetScore() == 0) {
            if (currentPlayer.GetName() == _player1.GetName())
                p1GameWins++;
            else if (currentPlayer.GetName() == _player2.GetName())
                p2GameWins++;
            break;
        }

        if (currentPlayer.GetName() == _player1.GetName()) {
            _player1 = currentPlayer;
            currentPlayer = _player2;
        } else {
            _player2 = currentPlayer;
            currentPlayer = _player1;
        }
    }
}

void Game::PlayMatch() {
    for (ushort i = 0; i < 13; ++i) {
        PlaySet();
        if (p1SetWins == 7 || p2SetWins == 7) {
            array<ushort, 2> result = {p1SetWins, p2SetWins};
            _matches.push_back(result);
            p1SetWins = 0;
            p2SetWins = 0;
            break;
        }
    }
}

void Game::PlaySet() {
    // Set loop
    for (int i = 0; i < 5; ++i) {
        (IsPlayerVsAI()) ? PlayGameUvsCPU() : PlayGameUvsU();
        if (p1GameWins == 3 || p2GameWins == 3) {
            (p1GameWins == 3) ? p1SetWins++ : p2SetWins++;
            p1GameWins = 0;
            p2GameWins = 0;
            break;
        }
    }
}

void Game::PlayGameUvsCPU() {
    // Game loop
    Player currentPlayer;
    _player1.Reset();
    _player2.Reset();
    if (_firstThrower) currentPlayer = _player1;
    else currentPlayer = _player2;
    _firstThrower = !_firstThrower;
    while (true) {
        if (currentPlayer.IsCPU())
            currentPlayer = SimulateTurnVsU(currentPlayer);
        else currentPlayer = PlayTurn(currentPlayer);
        if (currentPlayer.GetScore() == 0) {
            if (currentPlayer.GetName() == _player1.GetName())
                p1GameWins++;
            else if (currentPlayer.GetName() == _player2.GetName())
                p2GameWins++;
            break;
        }

        if (currentPlayer.GetName() == _player1.GetName()) {
            _player1 = currentPlayer;
            currentPlayer = _player2;
        } else {
            _player2 = currentPlayer;
            currentPlayer = _player1;
        }
    }
}

void Game::PlayGameUvsU() {
    // Game loop
    Player currentPlayer;
    _player1.Reset();
    _player2.Reset();
    if (_firstThrower) currentPlayer = _player1;
    else currentPlayer = _player2;
    _firstThrower = !_firstThrower;
    while (true) {
        if (int x = 2);
        currentPlayer = SimulateTurn(currentPlayer);
        if (currentPlayer.GetScore() == 0) {
            if (currentPlayer.GetName() == _player1.GetName())
                p1GameWins++;
            else if (currentPlayer.GetName() == _player2.GetName())
                p2GameWins++;
            break;
        }

        if (currentPlayer.GetName() == _player1.GetName()) {
            _player1 = currentPlayer;
            currentPlayer = _player2;
        } else {
            _player2 = currentPlayer;
            currentPlayer = _player1;
        }
    }
}


Player Game::SimulateTurn(Player player) {
    Player currentPlayer = player;

    for (ushort i = 0; i < 3; i++) {
        Target target = CalculateTarget(currentPlayer);
        SimulateThrowAt(target, currentPlayer);
        // if the player has won
        if (currentPlayer.GetScore() == 0) break;
        // if the player has busted
        if (currentPlayer.GetScore() < 2) return player;
    }

    return currentPlayer;
}

Player Game::SimulateTurnVsU(Player player) {
    Player currentPlayer = player;

    for (ushort i = 0; i < 3; i++) {
        Target target = CalculateTarget(currentPlayer);
        PlayThrowAt(target, currentPlayer);
        // if the player has won
        if (currentPlayer.GetScore() == 0) break;
        // if the player has busted
        if (currentPlayer.GetScore() < 2) return player;
    }

    return currentPlayer;
}

Player Game::PlayTurn(Player player) {
    Player currentPlayer = player;
    ushort playerTargetScore = 0;
    ushort playerMultiplier = 0;

    for (ushort i = 0; i < 3; i++) {
        do {
            GameClearScreen();
            playerTargetScore = UserIO::uShort("Your target [1 - 20]: ");
        } while (!playerTargetScore || playerTargetScore > 20);

        do {
            // Issue: Clang-Tidy: Narrowing conversion from 'int' to signed type 'char' is implementation-defined
            // Fix  : Explicitly defining char as unsigned as the implementation of char is decided at compile time an differs depending on the compiler
            unsigned char input = UserIO::String("Would you like to aim for a (S)ingle, (D)ouble, or (T)riple? : ",
                                                 false)[0];
            input = tolower(input);
            if (input == 's') playerMultiplier = Single;
            else if (input == 'd') playerMultiplier = Double;
            else if (input == 't') playerMultiplier = Triple;
            else {
                GameClearScreen();
                cout << "Your input is not valid!\nYour target [1 - 20]: " << to_string(playerTargetScore) << endl;
                continue;
            }
            break;
        } while (true);

        if (playerMultiplier == Single) PlayThrowAt(Target(playerTargetScore), currentPlayer);
        else if (playerMultiplier == Double) PlayThrowAt(Target(playerTargetScore, 2), currentPlayer);
        else PlayThrowAt(Target(playerTargetScore, 3), currentPlayer);

        // if the player has won
        if (currentPlayer.GetScore() == 0) break;
        // if the player has busted
        if (currentPlayer.GetScore() < 2) return player;
    }

    return currentPlayer;
}

bool IsMultipleOf(int multipleOf, int input) {
    return input % multipleOf == 0;
}

bool Game::IsPossibleScore(ushort input) {
    return input <= 22 ||
           (IsMultipleOf(3, input) && input <= 60) ||
           (IsMultipleOf(2, input) && input <= 40);
}

Target Game::calcRange(short range) {
    if (range <= 20) return Target(range);
    if (range <= 40) return Target(range / 2, 2);
    return Target(range / 3, 3);
}

Target Game::CalculateTarget(Player currentPlayer) {
    short currentScore = currentPlayer.GetScore();

    // 1 dart win
    if (currentScore == 50) return Target(50); // bull win
    if (!(currentScore % 2)) return Target(currentScore / 2, 2); // double win

    // 2 dart win
    // Dart 1 Reduce to 50 or a double
    // Dart 2 hit the dart <-- handled by 1 dart win
    if (currentScore <= 100 && (IsPossibleScore(currentScore - 50) ||
                                IsPossibleScore(currentScore - 60))) {
        short rangeToBull = currentScore - short(50);
        ushort rangeToDouble20 = rangeToBull + 10;
        // throw for bull
        if (rangeToBull > 0) {
            // aim to get to 50
            if (IsPossibleScore(rangeToBull)) {
                if (rangeToBull <= 20) return Target(rangeToBull);
                if (rangeToBull <= 40) return Target(rangeToBull / 2, 2);
                return Target(rangeToBull / 3, 3);
                // try to hit bull
            }
        }
        // impossible to score range for bull

        // aim to get 40
        if (rangeToDouble20 > 0) {
            if (IsPossibleScore(rangeToDouble20)) {
                if (rangeToDouble20 <= 20) return Target(rangeToDouble20);
                if (rangeToDouble20 <= 40) return Target(rangeToDouble20 / 2, 2);
                return Target(rangeToDouble20 / 3, 3);
            }
        }

        // The range between the player's score and the bull/40 is not
        // a value that can be scored

        // if the score is lower than 40
        // this value is odd as 1 dart win would handle
        // any even values less than 41
        if (currentScore < 40) {
            // Aim for 32 for double 16 win
            if (currentScore > 32) return Target(currentScore - 32);
            // Score is <= 31
            // 3 is the best to throw for as there are odd numbers either  side of 3
            // (19,17) - hitting any of these three will result in an even number
            // meaning that a double can be attempted on the next throw
            return Target(3);
        }
    }

    // 3 dart win
    if (currentScore <= 160) {
        short rangeToBull = currentScore - 50;
        // if bull in 1 dart reach
        if (rangeToBull <= 60) return calcRange(rangeToBull);
    }
    // bull more than 60 points away - score as high as possible
    return Target(20, 3);
}

void Game::SimulateThrowAt(Target target, Player &player) {
    ushort randTarget;
    // If the target is a multiplier make it harder to hit
    (target.IsMultiplied()) ? randTarget = 110 : randTarget = 100;
    // random side
    bool direction = rand() % 2;

    // the player misses
    if ((rand() % randTarget > player.GetAccuracy()) && player.GetAccuracy() != 100) {
        // 20% chance of missing entirely when aiming for doubles
        if (target.GetMultiplier() == 2 && rand() % 100 < 20) return;

        // Hit a neighbouring section
        ushort index = 0;
        // calc neighbouring sections
        // if not bull
        if (target.GetValue() != 50) {
            if (target.GetValue() != 25) {
                // Find the selected value in array
                for (ushort i = 0; i < 20; i++) if (_board[i] == target.GetValue()) index = i;
            } else if (direction) index = 10;
        }
        // left
        if (direction) { if (index == 0) index = 19; }
            // right
        else { if (index == 19) index = 0; }



        // if bull choose random number to hit instead
        if (target.GetValue() == 25) index += rand() % 10;

        target.SetTarget(_board[index]);

        if (target.GetMultiplier() == 1) {
            // 15% chance of hitting multiplier if not aiming for a multiplier
            if (rand() % 100 < 15) target.SetMultiplier(1);
        } else {
            // 55% chance of hitting multiplier if aiming for a multiplier
            if (rand() % 100 < 55) target.SetMultiplier(target.GetMultiplier());
        }

        // new target has been hit
    }


    player.SetLastTarget(target);

    // take hit from score
    player.ReduceScore(target.GetValue(true));

}

void Game::PlayThrowAt(Target target, Player &player) {
    string msg = player.GetName() + " throws at ";
    bool miss = false;
    if (target.GetMultiplier() == Triple) msg += "triple ";
    else if (target.GetMultiplier() == Double) msg += "double ";
    msg += to_string(target.GetValue()) + "\n";

    ushort randTarget;
    // If the target is a multiplier make it harder to hit
    (target.IsMultiplied()) ? randTarget = 110 : randTarget = 100;
    // random side
    bool direction = rand() % 2;

    // the player misses
    if ((rand() % randTarget > player.GetAccuracy()) && player.GetAccuracy() != 100) {
        miss = true;
        msg += player.GetName() + " missed!\n";
        // 20% chance of missing entirely when aiming for doubles
        if (target.GetMultiplier() == 2 && rand() % 100 < 20) {
            msg += player.GetName() + " missed the player area completely and scored 0!";
            return;
        }

        // Hit a neighbouring section
        ushort index = 0;
        // calc neighbouring sections
        // if not bull
        if (target.GetValue() != 50) {
            if (target.GetValue() != 25) {
                // Find the selected value in array
                for (ushort i = 0; i < 20; i++) if (_board[i] == target.GetValue()) index = i;
            } else if (direction) index = 10;
        }
        // left
        if (direction) { if (index == 0) index = 19; }
            // right
        else { if (index == 19) index = 0; }

        // if bull choose random number to hit instead
        if (target.GetValue() == 25) index += rand() % 10;

        target.SetTarget(_board[index]);

        if (target.GetMultiplier() == 1) {
            // 15% chance of hitting multiplier if not aiming for a multiplier
            if (rand() % 100 < 15) target.SetMultiplier(1);
        } else {
            // 55% chance of hitting multiplier if aiming for a multiplier
            if (rand() % 100 < 55) target.SetMultiplier(target.GetMultiplier());
        }

    }
    // new target has been hit
    msg += player.GetName() + " hits ";
    if (target.GetMultiplier() == Triple) msg += "triple ";
    else if (target.GetMultiplier() == Double) msg += "double ";
    msg += to_string(target.GetValue()) + ((miss) ? "instead!" : "") + "\n";
    player.SetLastTarget(target);
    // take hit from score
    player.ReduceScore(target.GetValue(true));
    if (player.IsCPU()) msg += player.GetName() + " now has a score of " + to_string(player.GetScore()) + "!\n\n";
}

string Game::GetReport() {
    string msg = "These are the results of " + to_string(_iterations) + " matches:\n";

    array<ushort, 14> outcomes = {0,  //  0 - 7:0
                                  0,  //  1 - 7:1
                                  0,  //  2 - 7:2
                                  0,  //  3 - 7:3
                                  0,  //  4 - 7:4
                                  0,  //  5 - 7:5
                                  0,  //  6 - 7:6
                                  0,  //  7 - 0:7
                                  0,  //  8 - 1:7
                                  0,  //  9 - 2:7
                                  0,  // 10 - 3:7
                                  0,  // 11 - 4:7
                                  0,  // 12 - 5:7
                                  0}; // 13 - 6:7

    // calculate outcome
    for (ushort i = 0; i < _matches.size(); ++i) {
        array<ushort, 2> match = _matches[i];
        // if player 1 won
        if (match[0] == 7)
            outcomes[match[1]]++;
        else outcomes[match[0] + 7]++;
    }

    // average outcomes
    array<float, 14> avgOutcomes =
            {0.0f,  //  0 - 7:0
             0.0f,  //  1 - 7:1
             0.0f,  //  2 - 7:2
             0.0f,  //  3 - 7:3
             0.0f,  //  4 - 7:4
             0.0f,  //  5 - 7:5
             0.0f,  //  6 - 7:6
             0.0f,  //  7 - 0:7
             0.0f,  //  8 - 1:7
             0.0f,  //  9 - 2:7
             0.0f,  // 10 - 3:7
             0.0f,  // 11 - 4:7
             0.0f,  // 12 - 5:7
             0.0f}; // 13 - 6:7

    for (ushort i = 0; i < 14; ++i) {
        ushort outcome = outcomes[i];
        avgOutcomes[i] = (float(outcome) / float(_iterations)) * 100;
    }

    msg += "Result\t\tFrequency\n" + _player1.GetName() + " : " + _player2.GetName() + "\n";
    for (ushort i = 0; i < 7; ++i)
        msg += to_string(7) + ":" + to_string(i) + "\t\t" + to_string(avgOutcomes[i]).substr(0, 5) + "%\n";

    msg += "---\t\t---------\n";

    for (ushort i = 0; i < 7; ++i)
        msg += to_string(i) + ":" + to_string(7) + "\t\t" + to_string(avgOutcomes[i + 7]).substr(0, 5) + "%\n";

    ushort p1TotalWins = 0;
    ushort p2TotalWins = 0;
    for (int i = 0; i < 14; ++i) {
        if (i < 7) p1TotalWins += outcomes[i];
        else p2TotalWins += outcomes[i];
    }

    float highest;
    bool p1Wins = (p1TotalWins > p2TotalWins);
    ushort lower, upper;

    if (p1Wins) upper = 7;
    else {
        lower = 7;
        upper = 14;
    }

    ushort index;
    for (int i = lower; i < upper; ++i) {
        float outcome = avgOutcomes[i];
        if (outcome > highest) {
            highest = outcome;
            index = i;
        }
    }

    msg += "\nOut of " + to_string(_iterations) + " matches, the winner, ";

    Player winner;
    int winnerTotalWins;
    Player loser;
    int loserTotalWins;
    // p1 won

    if (p1Wins) {
        winner = _player1;
        winnerTotalWins = p1TotalWins;
        loserTotalWins = p2TotalWins;
        loser = _player2;
    } else {
        winner = _player2;
        winnerTotalWins = p2TotalWins;
        loserTotalWins = p1TotalWins;
        loser = _player1;
    }

    msg += winner.GetName();

    float winnerTotalWinsPercentage = float(winnerTotalWins) / float(_iterations) * 100.0f;
    float loserTotalWinsPercentage = float(loserTotalWins) / float(_iterations) * 100.0f;

    msg += ",\nwon " + to_string(winnerTotalWins) + " matches (" + to_string(winnerTotalWinsPercentage).substr(0, 5) +
           "%)\nand " + to_string(highest).substr(0, 5) + "% of the matches were won with a score of ";
    if (index == 0 || index == 7) msg += "7 to 0  ";
    else if (index == 1 || index == 8) msg += "7 to 1 ";
    else if (index == 2 || index == 9) msg += "7 to 2 ";
    else if (index == 3 || index == 10) msg += "7 to 3 ";
    else if (index == 4 || index == 11) msg += "7 to 4 ";
    else if (index == 5 || index == 12) msg += "7 to 5 ";
    else if (index == 6 || index == 13) msg += "7 to 6 ";

    msg += "\nwith an accuracy of " + to_string(winner.GetAccuracy()) + "%!\n";


    /*************LOSER**************/
    if (!p1Wins) {
        lower = 0;
        upper = 7;
    } else {
        lower = 7;
        upper = 14;
    }

    highest = 0.0f;

    for (int i = lower; i < upper; ++i) {
        float outcome = avgOutcomes[i];
        if (outcome > highest) {
            highest = outcome;
            index = i;
        }
    }

    msg += "\nOut of " + to_string(_iterations) + " matches, the loser, " + loser.GetName();
    msg += ",\nwon " + to_string(loserTotalWins) + " matches (" + to_string(loserTotalWinsPercentage).substr(0, 5) +
           "%)\nand " + to_string(highest).substr(0, 5) + "% of the matches were won with a score of ";

    if (index == 0 || index == 7) msg += "7 to 0  ";
    else if (index == 1 || index == 8) msg += "7 to 1 ";
    else if (index == 2 || index == 9) msg += "7 to 2 ";
    else if (index == 3 || index == 10) msg += "7 to 3 ";
    else if (index == 4 || index == 11) msg += "7 to 4 ";
    else if (index == 5 || index == 12) msg += "7 to 5 ";
    else if (index == 6 || index == 13) msg += "7 to 6 ";

    msg += "\nwith an accuracy of " + to_string(loser.GetAccuracy()) + "%!\n";
    return msg;
}

