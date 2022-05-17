#include "Item.hpp"

int Item::count = 0;

Item::Item (string name, string type, float netCost) {

    count++;
    this -> id = count;
    this -> name = name;
    this -> type = type;
    this -> date = "0";
    this -> netCost = netCost;
    this -> finalCost = 0;
    this -> market = nullptr;
    this -> seller = nullptr;
    this -> buyer = nullptr;
}

Item::Item (int id, string name, string type, string date, float netCost, float finalCost, Market* market, Person* seller, Person* buyer) {

    count = max(id, count+1);
    this -> id = id;
    this -> name = name;
    this -> type = type;
    this -> date = date;
    this -> netCost = netCost;
    this -> finalCost = finalCost;
    this -> market = market;
    this -> seller = seller;
    this -> buyer = buyer;
}

Item::~Item () {}

int Item::getId () const {

    return this -> id;
}

string Item::getName () const {

    return this -> name;
}

string Item::getType () const {

    return this -> type;
}

string Item::getDate () const {

    return this -> date;
}

float Item::getNetCost () const {

    return this -> netCost;
}

float Item::getFinalCost () const {

    return this -> finalCost;
}

Market* Item::getMarket () const {

    return this -> market;
}

Person* Item::getSeller () const {

    return this -> seller;
}

Person* Item::getBuyer () const {

    return this -> buyer;
}

void Item::showInfo (bool sold) const {

    cout << string(6, '-') << " Item " << this -> getId() << " (" << this -> getType() << ") " << string(6, '-') << endl;
    cout << "Name: " << this -> getName() << endl;
    cout << "Market: " << this -> getMarket() -> getName() << endl;
    cout << "Net Cost: " << this -> getNetCost() << endl;
    if (sold) {
        cout << "Final Cost: " << this -> getFinalCost() << endl;
        cout << "Seller: " << this -> getSeller() -> getName() << endl;
        cout << "Buyer: " << this -> getBuyer() -> getName() << endl;
        cout << "Transaction Date: " << this -> getDate() << endl;
    }
}

void Item::setDate (string date) {

    this -> date = date[date.size()-1] == '\n' ? date.substr(0, date.size()-1) : date;
}

void Item::setFinalCost (float finalCost) {

    this -> finalCost = finalCost;
}

void Item::setMarket (Market* market) {

    this -> market = market;
}

void Item::setSeller (Person* seller) {

    this -> seller = seller;
}

void Item::setBuyer (Person* buyer) {

    this -> buyer = buyer;
}