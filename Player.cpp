//
// Created by ben on 27/03/2020.
//

#include "Player.h"
#include <string>

typedef unsigned short ushort;


string Player::GetName() {
    return _name;
}

void Player::SetName(string name) {
    if (name == "") return;
    _name = name;
}

ushort Player::GetAccuracy() {
    return _accuracy;
}

void Player::SetAccuracy(ushort accuracy) {
    if (accuracy > 100) accuracy = 100;
    else _accuracy = accuracy;
}

short Player::GetScore() {
    return _score;
}

void Player::ReduceScore(ushort score) {
    _score -= score;
}

void Player::Reset(){
    _score = 501;
}

bool Player::IsCPU() {
    return _isCPU;
}

void Player::SetCPU(bool value){
    _isCPU = value;
}

Target Player::GetLastTarget (){
    return _lastTarget;
}

void Player::SetLastTarget(Target target){
    _lastTarget = target;
}