#include<iostream>
#include "card.hpp"
using namespace std;

#define NULL __null
using namespace  ariel;


card::card(int _number ,string _shape)
{
    this->number =_number;
    this->shape =_shape;
}

card:: card(const card& _card):number(_card.number),shape(_card.shape){

}
card& card:: operator=(const card& other){
    if(this != &other){
        number = other.number;
        shape = other.shape;
    }
    return *this;
}

card:: card(card&& other) noexcept:number(other.number),shape(other.shape){

}
card& card:: operator=(card&& other) noexcept{
    if(this != &other){
        number = other.number;
        shape = other.shape;
    }
    return *this;
}
card::~card()
{
}

    void card:: setNumber(int num){
        number = num;
    }
    void card:: setShape(string _shape){
        shape = _shape;
    }
    void card:: printCard(){
        cout<<number<<"-"<< shape ;
    }
    int card:: getNumber(){
        return number;
    }
    string card:: getShape(){
        return shape;
    }
