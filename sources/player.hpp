
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <iostream>
#include "card.hpp"
using namespace std;
namespace  ariel{


class Player
{
  private:
    string name;
    vector<card> deckPlay, deckEarn;
    int countWin,countLose,countDraw;

  public:

    //constructor 
    Player(std::string _name);
    
    //Copy Constructor
    Player(const Player& _player);
    
    //Move Constructor
    Player(Player&& other) noexcept;
    
    //copy assignment operator
    Player& operator=(const Player& other);
    
    //move assignment operator
    Player& operator=(Player&& other) noexcept;

    ~Player();
    int  stacksize();//prints the amount of cards left. should be 21 but can be less if a draw was played
    int cardesTaken(); // prints the amount of cards this player has won. 
    void setName(string n);
    string getName();
    void setCardPlay(card);
    void setCardEarn(card);
    card getCardPlay(); //return one card from end the deckPlay
    vector<card> getDeckEarn();
    void deleteCardFromEndDeck();// delete card that used from deckPlay
    double getCountWin();
    double getCountLose();
    double getCountDraw();
    void  increaseCountWin();
    void increaseCountLose();
    void increaseCountDraw();
    vector<card> getDeckPlay();
    void updateDeckPlay(vector<card>);
    bool deckPlayNOTempty();
  };

}
#endif