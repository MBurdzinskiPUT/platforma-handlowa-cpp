#include "Estate.hpp"

Estate::Estate (string name, float netCost, float propertyTax)
    : Item(name, "Estate", netCost) {

    this -> propertyTax = propertyTax;
}

Estate::Estate (int id, string name, string date, float netCost, float finalCost, Market* market, Person* seller, Person* buyer, float propertyTax)
    : Item(id, name, "Estate", date, netCost, finalCost, market, seller, buyer) {

    this -> propertyTax = propertyTax;
}

Estate::~Estate () {}

float Estate::calculateTax () {

    return (this -> netCost) * (1 + (this -> salesTax) + (this -> propertyTax));
}

float Estate::totalCost (double distance) {

    return (this -> calculateTax());
}

float Estate::getPropertyTax () const {

    return this -> propertyTax;
}

void Estate::showInfo (bool sold) const {

    Item::showInfo(sold);
    if (!sold) {
        cout << "Property Tax: " << this -> getPropertyTax() * 100 << "%" << endl;
    }
}