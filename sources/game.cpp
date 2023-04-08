
#include <iostream>
#include "player.hpp"
#include "game.hpp"
#include "card.hpp"
#include<vector>
#include <random>
#include <cstdlib>
#include <time.h>
using namespace std;

using namespace  ariel;

Game::Game(Player &pl1,Player &pl2):player1(pl1),player2(pl2),Deck(),statsgame()
{   
    countTurn = 0;
    namewinner = "";
    statsTurn = "";
    createDeck();
    shuffleDeck();
    dealingCards();
}

Game::Game(const Game& _game):player1(_game.player1),player2(_game.player2),Deck(),statsgame(){
    countTurn = 0;
    namewinner = "";
    statsTurn = "";
}

Game &Game:: operator=(const Game& other){
    if(this != &other){
        player1 = other.player1;
        player2 = other.player2;
    }
    return *this;
}

Game &Game:: operator=(Game&& other)noexcept{
    if(this != &other){
        player1 = other.player1;
        player2 = other.player2;
    }
    return *this;
}

Game::Game(Game&& other)noexcept:player1(other.player1),player2(other.player2) {
     
}

Game::~Game()
{
    cout<<"this game delete"<< endl;


}

void Game::playTurn(){
    vector<card> tempcard;
    bool draw = true;
    card cp1,cp2;

    while(draw)
    {
        card cp1;
        card cp2;

        if(player1.deckPlayNOTempty() && player2.deckPlayNOTempty()){

            countTurn++;

            cp1 = player1.getCardPlay();//return one card from end the deckPlay - player 1
            cp2 = player2.getCardPlay();//return one card from end the deckPlay - player 2

            player1.deleteCardFromEndDeck();
            player2.deleteCardFromEndDeck();
            
            if(cp1.getNumber() == cp2.getNumber()){//check if draw
                tempcard.emplace_back(cp1);
                tempcard.emplace_back(cp2);

                player1.increaseCountDraw();
                player2.increaseCountDraw();
                
                statsTurn += player1.getName()+ " played " + to_string(cp1.getNumber())+ " of " + cp1.getShape() +
                            ", "+player2.getName() + " played " + to_string(cp2.getNumber())+ " of " + cp2.getShape()+
                            ". Draw. " ;

                if(player1.stacksize() <= 1 && player2.stacksize() <= 1){

                    player1.setCardPlay(cp1);
                    player2.setCardPlay(cp2);
                    while(player1.stacksize() != 0){
                        player1.setCardEarn(player1.getCardPlay());
                        player1.deleteCardFromEndDeck();
                    }

                    while(player2.stacksize() != 0){
                        player2.setCardEarn(player2.getCardPlay());
                        player2.deleteCardFromEndDeck();
                    }
                    tempcard.clear();
                }
                else{
                    
                    tempcard.emplace_back(player1.getCardPlay());
                    player1.deleteCardFromEndDeck();
                    tempcard.emplace_back(player2.getCardPlay());
                    player2.deleteCardFromEndDeck();
                }
                
                
                draw = true;
            }
            else if(cp1.getNumber() - cp2.getNumber() == 12){//check for 2 win 14 for player2
                player2_WinTurn(cp1,cp2,tempcard);
                draw = false;
                tempcard.clear();

            }
            else if(cp1.getNumber() - cp2.getNumber() == -12){//check for 2 win 14 for player1
                player1_WinTurn(cp1,cp2,tempcard);
                draw = false;
                tempcard.clear();
            }
            else if (cp1.getNumber() > cp2.getNumber())//check if player1 win the turn
            {
                player1_WinTurn(cp1,cp2,tempcard);
                draw = false;
                tempcard.clear();
            }
            else if(cp1.getNumber() < cp2.getNumber()){//check if player2 win the turn
                player2_WinTurn(cp1,cp2,tempcard);
                draw = false;
                tempcard.clear();

            }
        }
        else{

            // printLog();
            // cout<<"Turn: " << countTurn<<endl;
            // cout<<"draw: " << player1.getCountDraw()<<endl;

            throw ("ERROR: The players have run out of cards, it is not possible to make another turn.");
                return;
        }
    }

}  

void Game:: playAll(){
    while(player1.deckPlayNOTempty() && player2.deckPlayNOTempty()){
        playTurn();
    }    
}

void Game::printWiner(){

    if(player1.stacksize() == 0 && player2.stacksize() == 0 ){

        if (player1.cardesTaken() > player2.cardesTaken())
        {
            setNameWinner(player1.getName());
            cout << "THE WINNER IS: "<< getNameWinner() <<endl;
        }
        else if(player1.cardesTaken() < player2.cardesTaken()){
            setNameWinner(player2.getName());
            cout << "THE WINNER IS: "<< getNameWinner() <<endl;
        }
        else{
        setNameWinner("draw");
        cout << "There are no winners, the game ends in a "<<getNameWinner()<<endl;
        }
    }
}

void Game::printLog(){

    int indexturn = 1;
    cout << "\n\t\t\t----------------------PRINT LOG----------------------\n"<<endl;
        for (auto i = statsgame.begin(); i != statsgame.end(); ++i){
            cout<<indexturn++ <<"." << (*i)<<endl ;
                
        }
}

void Game::printStats(){
    cout<<"\n\t\t\t----------------------Stats Of The Game----------------------\n"<<endl;
    double rateWin_1 =  (player1.getCountWin() /countTurn)*100.0;
    double rateLose_1 = (player1.getCountLose()/countTurn)*100.0;
    double rateDraw_1 = (player1.getCountDraw()/countTurn)*100.0;

    double rateWin_2 =  (player2.getCountWin() /countTurn)*100.0;
    double rateLose_2 = (player2.getCountLose()/countTurn)*100.0;
    double rateDraw_2 = (player2.getCountDraw()/countTurn)*100.0;

    cout<< "Name Player: "<< player1.getName()<<"\nNumber of turns: "<< countTurn 
        << "\nThe number of wins: "<<player1.getCountWin()<<"\nThe number of win cards: "<<player1.cardesTaken() << "\nThe amount of losses: "
        << player1.getCountLose()<< "\nThe amount of draw: "<< player1.getCountDraw()
        << "\nWin rate : "<< rateWin_1 <<"%\nLoss rate: "<< rateLose_1
        << "%\nThe draw rate: "<< rateDraw_1 <<"%\nWinning cards:\n"<<endl;

    vector<card> deckWin = player1.getDeckEarn();
    for (auto i = deckWin.begin(); i != deckWin.end(); ++i){
        
        (*i).printCard();
        if((*i).getNumber() != deckWin.back().getNumber()&&(*i).getShape() != deckWin.back().getShape())
                cout<<" , ";
    }
    deckWin.clear();

    cout<<"\n\n";

    cout<< "Name Player: "<< player2.getName()<<"\nNumber of turns: "<< countTurn 
    << "\nThe number of wins: "<<player2.getCountWin()<<"\nThe number of win cards: "<<player2.cardesTaken() << "\nThe amount of losses: "
    << player2.getCountLose()<< "\nThe amount of draw: "<< player2.getCountDraw()
    << "\nWin rate : "<< rateWin_2<<"%\nLoss rate: "<<rateLose_2
    << "%\nThe draw rate: "<< rateDraw_2 <<"%\nWinning cards:\n"<<endl;
    
    deckWin = player2.getDeckEarn();

    for (auto i = deckWin.begin(); i != deckWin.end(); ++i){
        (*i).printCard();
        if((*i).getNumber() != deckWin.back().getNumber()&&(*i).getShape() != deckWin.back().getShape())
            cout<<" , ";
    }
    deckWin.clear();
    cout<<"\n\n";
}

void Game::printLastTurn(){

    if(player1.cardesTaken() == 0 && player2.cardesTaken() == 0){
        throw("ERROR: No turns have been made in the game yet");
    }
    else{
        cout <<"\n"<< statsgame.back() << endl;
    }
        
}

void Game:: createDeck(){
     
    card temp;
    string _shape[4]={"Hart","Diamond","Spades","Clubs"};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 2; j < 15; j++)
        {   
            temp.setNumber(j);
            temp.setShape(_shape[i]);
            Deck.emplace_back(temp);
        }
        
    }

}

void Game:: swapp(size_t key,size_t ran){
    card car = Deck[key];
    Deck[key] = Deck[ran];
    Deck[ran] = car;

}

void Game:: shuffleDeck(){

    srand(time(0));
    for (size_t k = 0; k < Deck.size(); k++) {
    
        size_t r = k + ((unsigned long)rand() % (Deck.size() - k));
        swapp(k,r);  
    }
}

void Game:: setNameWinner(string _name){
    namewinner = _name;
}

string Game:: getNameWinner(){
    return namewinner;
}

void Game:: dealingCards(){
    
    int sizeDeck = Deck.size();
   

    for(int i = 0; i < sizeDeck/2; i++){
        player1.setCardPlay(Deck.back());
        Deck.pop_back();
        player2.setCardPlay(Deck.back());
        Deck.pop_back();
    }
}

void Game:: player1_WinTurn(card cp1,card cp2,vector<card> tempcard){
    player1.setCardEarn(cp1);
    player1.setCardEarn(cp2);

    while(!tempcard.empty()){
        player1.setCardEarn(tempcard.back());
        tempcard.pop_back();
    }

    player1.increaseCountWin();
    player2.increaseCountLose();

    statsTurn += player1.getName()+ " played " + to_string(cp1.getNumber())+ " of " + cp1.getShape() +
                ", "+player2.getName() + " played " + to_string(cp2.getNumber())+ " of " + cp2.getShape()+
                ". "+player1.getName()+ " wins\n" ;
    statsgame.emplace_back(statsTurn);
    statsTurn = "";
  }

void Game:: player2_WinTurn(card cp1,card cp2,vector<card> tempcard){
    this->player2.setCardEarn(cp2);
    this->player2.setCardEarn(cp1);

    while(!tempcard.empty()){
        player2.setCardEarn(tempcard.back());
        tempcard.pop_back();
    }
    this->player2.increaseCountWin();
    this->player1.increaseCountLose();

    statsTurn += player1.getName()+ " played " + to_string(cp1.getNumber())+ " of " + cp1.getShape() +
                ", "+player2.getName() + " played " + to_string(cp2.getNumber())+ " of " + cp2.getShape()+
                ". "+player2.getName()+ " wins\n" ;
    statsgame.emplace_back(statsTurn);
    statsTurn = "";
}