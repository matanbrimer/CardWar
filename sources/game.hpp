#ifndef GAME_H
#define GAME_H
#include <vector>
 
#include "player.hpp"
#include "card.hpp"
using namespace std;
namespace ariel{

class Game
{
    
private:
    Player &player1, &player2;
    vector<card> Deck;
    string namewinner;
    int countTurn;
    string statsTurn;
    vector<string> statsgame;
public:

    
    //constructor
    Game(Player& pl1, Player& pl2);

    //Copy Constructor
    Game(const Game&);

    //Move Constructor
    Game(Game&& other)noexcept;

    //copy assignment operator
    Game& operator=(const Game& other) ; 

    //move assignment operator
    Game& operator=(Game&& other)noexcept; // Define move assignment operator
    ~Game();
  
    
    void playAll();
    void printWiner(); 
    void printLog();
    void printStats();
    void playTurn();
    void printLastTurn();
    void createDeck();
    void shuffleDeck();
    vector<card> getDeck();
    void setNameWinner(string _name);
    string getNameWinner();
    void dealingCards();
    void player1_WinTurn(card,card,vector<card>);
    void player2_WinTurn(card,card,vector<card>);
    void printCardsWin(Player);
    void  swapp(size_t ,size_t );
    
};






} 
#endif