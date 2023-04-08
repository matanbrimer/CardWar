
#ifndef CARD_H
#define CARD_H
#include<iostream>


using namespace std;
namespace  ariel{

class card
{
private:
    int number;
    string shape;
public:
    //constructor 
    card(int _number = 0,string _shape = "");

   

    //Copy Constructor
    card(const card& _card);

    // Move Constructor
    card(card&& other) noexcept;

    //copy assignment operator
    card& operator=(const card& other);

    //move assignment operator
    card& operator=(card&& other) noexcept;
    ~card();

    void setNumber(int num);
    int getNumber();
    string getShape();
    void setShape(string shape);
    void printCard();
};


}
#endif