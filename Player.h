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
    Target _lastHit;
    bool _bust = false;
    bool _miss = false;
    bool _nonDoubleEnd = false;
    short _tempScore = 501;
public:
    short getTempScore() const;

    void setTempScore(short tempScore);

public:
    bool isNonDoubleEnd() const;

    void setNonDoubleEnd(bool nonDoubleEnd);

public:
    bool isMiss() const;

    void setMiss(bool miss);

public:
    bool isBust() const;

    void setBust(bool bust);

public:
    string GetName();

    void SetName(string);

    ushort GetAccuracy();

    void SetAccuracy(ushort);

    short GetScore();

    void ReduceScore(ushort);

    void Reset(bool resetScore = false);

    bool IsCPU();

    void SetCPU(bool value);

    Target GetLastTarget();

    void SetLastTarget(Target target);

    Target GetLastHit();

    void SetLastHit(Target hit);
};

#endif //DARTS501_PLAYER_H
