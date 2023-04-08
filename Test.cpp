#include <iostream>
#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"

using namespace std;
using namespace ariel;


TEST_CASE("check winer function "){

    Player pl1("Tony");
    Player pl2("Sonya");

    Game game(pl1,pl2);

    game.playAll();
    
    string nameWin = (pl1.cardesTaken()>pl2.cardesTaken())?pl1.getName():pl2.getName();
    
    // the value that return from getNameWinner() function will print in printWiner() function
    CHECK(game.getNameWinner() == nameWin);

}


// check if the numbers is correct
// 11 == jeck || 12 == queen || 13 == king || 1 == ace 
TEST_CASE("check min/max number card and if exist negativ number"){
    Player pl1("daniela");
    Player pl2("daniel");

    Game game(pl1,pl2);
    int min=100,max=0;
    bool negative = false;

    vector<card> deck = game.getDeck();
    for (auto i = deck.begin(); i != deck.end(); ++i){
        if((*i).getNumber() < min ){
            min = (*i).getNumber();
        }
        if((*i).getNumber() > max ){
            max = (*i).getNumber();
        }
        if((*i).getNumber() < 0){
            negative = true;
        }
    }
        
    CHECK(min == 1);// 1 == Ace
    CHECK(max == 13);//13 == King
    CHECK(negative == false);
    
}
/*
 The pack of cards is built using 4 repetitions of the numbers 1-13 where 
the sum of 1+2+..+13 is equal to 91 therefore if the pack was not shuffled 
the sum of the first 13 cards would still be 91

and the countShape need to be equal to ClubsClubs... (Clubs*13)
*/
TEST_CASE("Checking if the deck is mixed"){
    Player pl1("rami");
    Player pl2("dotan");
    
    Game game(pl1,pl2);
    int beforcountNumbers=0;
    string beforcountShape = "";

    int aftercountNumbers=0;
    string aftercountShape = "";
    game.createDeck();
    bool mixed = true;
    vector<card> deck = game.getDeck();

    for (std::vector<card>::size_type i = 0; i < 13 && deck.size() > 0; i++)
    {
        beforcountNumbers += deck.at(i).getNumber();
        beforcountShape += deck.at(i).getShape();
    }
    
    

    game.shuffleDeck();
    vector<card> deck2 = game.getDeck();
    for (std::vector<card>::size_type i = 0; i < 13 && deck2.size() > 0; i++)
    {
        aftercountNumbers += deck2.at(i).getNumber();
        aftercountShape += deck2.at(i).getShape();
    }

    bool checkMixed = false;
    if((beforcountNumbers != aftercountNumbers) && (beforcountShape != aftercountShape))
        checkMixed = true;
    
    CHECK(checkMixed == true);

}

TEST_CASE("size of deck"){

    Player pl1("roni");
    Player pl2("dan");

    Game game(pl1,pl2);

    CHECK(game.getDeck().size() == 52);


}
TEST_CASE("check amount of card for the player and in the deck after the division"){

    Player pl1("Alice");
    Player pl2("Daniel");

    Game game(pl1,pl2);
    game.shuffleDeck();
    game.dealingCards();
    cout<<"pl1.stacksize() == "<<pl1.stacksize()<<endl;
    cout<<"pl2.stacksize() == "<<pl2.stacksize()<<endl;
    cout<<"game.getDeck().size() == "<<game.getDeck().size()<<endl;
    CHECK(pl1.stacksize() == 26);
    CHECK(pl2.stacksize() == 26);
    CHECK(game.getDeck().size() == 0);


}
TEST_CASE("CHECK NOT THROWS"){
    Player pl1("Alice");
    Player pl2("Daniel");

    Game game(pl1,pl2);
    CHECK_NOTHROW(game.printWiner());
    CHECK_NOTHROW(game.createDeck());
    CHECK_NOTHROW(game.playAll());
    CHECK_NOTHROW(game.playTurn());
    CHECK_NOTHROW(game.printLastTurn());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
    CHECK_NOTHROW(game.shuffleDeck());
    CHECK_NOTHROW(pl1.cardesTaken());
    CHECK_NOTHROW(pl1.stacksize());


}
TEST_CASE("check void function "){

    Player pl1("fredy");
    Player pl2("shalom");

    Game game(pl1,pl2);
    
    CHECK(std::is_void<decltype(game.playAll())>::value);
    CHECK(std::is_void<decltype(game.playTurn())>::value);
    CHECK(std::is_void<decltype(game.printLastTurn())>::value);
    CHECK(std::is_void<decltype(game.printLog())>::value);
    CHECK(std::is_void<decltype(game.printStats())>::value);
    CHECK(std::is_void<decltype(game.printWiner())>::value);
    

}
