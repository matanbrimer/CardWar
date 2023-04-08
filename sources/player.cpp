
#include "player.hpp"
#include <iostream>
using namespace std;

using namespace  ariel;



Player::Player(string _name):name(_name), deckPlay(),deckEarn()
{   
    countLose = 0;
    countDraw = 0;
    countWin = 0;
}

Player::Player(const Player& _player):Player(_player.name){

}
Player& Player::operator=(const Player& other)
{
    if (this != &other)
    {
        name = other.name;
    }
    return *this;
}
Player::Player(Player&& other)noexcept: name(other.name)
{
}

Player& Player::operator=(Player&& other)noexcept
{
    if (this != &other)
    {
        name = other.name;
    }
    return *this;
}
Player::~Player()
{
    cout<<"delete player: "<< name << endl;

}

// return size of deck player
int Player::stacksize(){
    return deckPlay.size();
}

// return size of cards earn
int Player::cardesTaken(){
    return deckEarn.size();
}
bool Player:: deckPlayNOTempty(){
    return !deckPlay.empty();
}
void Player::setName(string n){
    this->name = n;
}

std::string Player::getName(){
    return name;
}

// push card from deck game to deck player
void Player:: setCardPlay(card card){
    deckPlay.emplace_back(card);
}

// push card of player + card earn
void Player:: setCardEarn(card card){
    deckEarn.emplace_back(card);
}

// return one card from end the deckPlay
card Player:: getCardPlay(){
        return deckPlay[deckPlay.size()-1];

        
}

// return the cards deck the player was win
vector<card> Player:: getDeckEarn(){
    return deckEarn;
}

// delete card that used from deckPlay
void Player:: deleteCardFromEndDeck(){
     if (!deckPlay.empty()) {
        deckPlay.pop_back();
    }
}




double Player:: getCountWin(){
    return countWin;
}

double Player:: getCountLose(){
    return countLose;
}

double Player:: getCountDraw(){
    return countDraw;
}

void Player:: increaseCountWin(){
     countWin++;
}

void Player:: increaseCountLose(){
     countLose++;
}

void Player:: increaseCountDraw(){
     countDraw++;
}

vector<card> Player:: getDeckPlay(){
    return deckPlay;
}

void Player:: updateDeckPlay(vector<card> newDeck){

    deckPlay.clear();
    deckPlay = newDeck;

}