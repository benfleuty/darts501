//
// Created by ben on 27/03/2020.
//

#include "Target.h"
typedef unsigned short ushort;

void Target::SetTarget(ushort target)
{
    _value = target;
}

void Target::SetMultiplier(ushort multiplier)
{
    _multiplier = multiplier;
}

ushort Target::GetMultiplier()
{
    return _multiplier;
}

bool Target::IsMultiplied()
{
    return (_multiplier > 1) ? true : false;
}

ushort Target::GetValue(bool multiply)
{
    return (multiply) ? _value * _multiplier : _value;
}
