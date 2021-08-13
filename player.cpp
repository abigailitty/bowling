//Abby Itty
//Player Implementation

#include <iostream>
#include <vector>
#include "player.h"

Player::Player(std::string& fn, std::string& ln, std::vector<int>& s)
{
    firstName = fn;
    lastName = ln;
    scores = s;
    finalScore = 0;
    gutterBalls = 0;
}

std::vector<int> Player::getScores() const
{
    return scores;
}

std::string Player::getFirstName() const
{
    return firstName;
}

std::string Player::getLastName() const
{
    return lastName;
}

int Player::getFinalScore() const
{
    return finalScore;
}

int Player::getGutterBalls() const
{
    return gutterBalls;
}

void Player::setFirstName(const std::string& fn)
{
    firstName = fn;
}

void Player::setLastName(const std::string& ln)
{
    lastName = ln;
}

void Player::setScores(const std::vector<int>& s)
{
    scores = s;
}

void Player::setFinalScore(int x)
{
    finalScore = x;
}

void Player::incGutterBalls()
{
    gutterBalls++;
}

bool operator< (const Player& first, const Player& second)
{
    if(first.getLastName() < second.getLastName())
        return true;
    else if(first.getLastName() > second.getLastName())
        return false;
    else
    {
        if(first.getFirstName() < second.getLastName())
            return true;
        else
            return false;
    }
}

bool finalSort(const Player& first, const Player& second)
{
    if(first.getFinalScore() > second.getFinalScore())
        return true;
    else
        return false;
}