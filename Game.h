//
// Created by ben on 27/03/2020.
//

#ifndef DARTS501_GAME_H
#define DARTS501_GAME_H

#include <array>

#include "Player.h"
#include "Target.h"

typedef unsigned int uint;
using namespace std;

class Game {
protected:
    Player _player1;
    Player _player2;
    uint _iterations = 0;

    ushort _board[20] = {
            20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5
    };

    bool _firstThrower = true;

    vector<array<ushort, 2>> _matches;

    void SimulateMatch();

    void SimulateSet();

    void SimulateGame();

    void PlayMatch();

    void PlaySet();

    void PlayGameUvsCPU();

    void PlayGameUvsU();


    ushort p1GameWins = 0;
    ushort p2GameWins = 0;
    ushort p1SetWins = 0;
    ushort p2SetWins = 0;

    static bool IsPossibleScore(ushort input);

    static Target calcRange(short range);

    static bool IsSimulation(Player, Player);

    bool IsPlayerVsAI();

public:
    Game() {}

    Game(Player player1, Player player2, uint iterations, bool firstThrower) {
        _player1 = std::move(player1);
        _player2 = std::move(player2);
        _iterations = iterations;
        _firstThrower = firstThrower;
    }

    void Start();

    void SimulateThrowAt(Target, Player &);

    void PlayThrowAt(Target, Player &);

    static Target CalculateTarget(Player);

    Player SimulateTurn(Player player);

    string GetReport();

    Player PlayTurn(Player player);

    Player SimulateTurnVsU(Player player);

    void GameClearScreen();
};


#endif //DARTS501_GAME_H
