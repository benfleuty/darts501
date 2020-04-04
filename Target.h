//
// Created by ben on 27/03/2020.
//

#ifndef DARTS501_TARGET_H
#define DARTS501_TARGET_H

typedef unsigned short ushort;

class Target
{
public:
    Target(){}

    Target(ushort value) {
        _value = value;
        _multiplier = 1;
    }

    Target(ushort value, ushort multiplier) {
        _value = value;
        _multiplier = multiplier;
    }

    void SetTarget(ushort);
    void SetMultiplier(ushort);
    ushort GetMultiplier();
    bool IsMultiplied();
    ushort GetValue(bool = false);

private:
    ushort _value = 0;
    ushort _multiplier = 1;

};



#endif //DARTS501_TARGET_H
