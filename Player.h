//
// Created by ben on 27/03/2020.
//

#ifndef DARTS501_PLAYER_H
#define DARTS501_PLAYER_H

#include <string>
#include <vector>
#include "Target.h"

using namespace std;
typedef unsigned short ushort;

class Player {
private:
    string _name = "";
    ushort _accuracy = 0;
    short _score = 501;
    bool _isCPU = true;
    Target _lastTarget;

public:
    string GetName();
    void SetName(string);
    ushort GetAccuracy();
    void SetAccuracy(ushort);
    short GetScore();
    void ReduceScore(ushort);
    void Reset();
    bool IsCPU();

    void SetCPU(bool value);

    Target GetLastTarget();
    void SetLastTarget(Target target);
};

#endif //DARTS501_PLAYER_H
