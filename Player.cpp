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

void Player::Reset(bool resetScore) {
    if(resetScore) _score = 501;
     _bust = false;
     _miss = false;
     _nonDoubleEnd = false;
}

bool Player::IsCPU() {
    return _isCPU;
}

void Player::SetCPU(bool value) {
    _isCPU = value;
}

Target Player::GetLastTarget() {
    return _lastTarget;
}

void Player::SetLastTarget(Target target) {
    _lastTarget = target;
}

Target Player::GetLastHit() {
    return _lastHit;
}

void Player::SetLastHit(Target hit) {
    _lastHit = hit;
}

bool Player::isBust() const {
    return _bust;
}

void Player::setBust(bool bust) {
    _bust = bust;
}

bool Player::isMiss() const {
    return _miss;
}

void Player::setMiss(bool miss) {
    _miss = miss;
}

bool Player::isNonDoubleEnd() const {
    return _nonDoubleEnd;
}

void Player::setNonDoubleEnd(bool nonDoubleEnd) {
    _nonDoubleEnd = nonDoubleEnd;
}

short Player::getTempScore() const {
    return _tempScore;
}

void Player::setTempScore(short tempScore) {
    Player::_tempScore = tempScore;
}
