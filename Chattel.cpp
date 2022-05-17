#include "Chattel.hpp"

Chattel::Chattel (string name, float netCost, float deliveryCost)
    : Item(name, "Chattel", netCost) {

    this -> deliveryCost = deliveryCost;
}

Chattel::Chattel (int id, string name, string date, float netCost, float finalCost, Market* market, Person* seller, Person* buyer, float deliveryCost)
    : Item(id, name, "Chattel", date, netCost, finalCost, market, seller, buyer) {

    this -> deliveryCost = deliveryCost;
}

Chattel::~Chattel () {}

float Chattel::calculateTax () {

    return (this -> netCost) * (1 + (this -> salesTax));
}

float Chattel::totalCost (double distance) {

    return (this -> calculateTax()) + sqrt((this -> deliveryCost) * distance);
}

float Chattel::getDeliveryCost () const {

    return this -> deliveryCost;
}

void Chattel::showInfo (bool sold) const {

    Item::showInfo(sold);
    if (!sold) {
        cout << "Delivery Cost: " << this -> getDeliveryCost() << "*" << endl;
    }
}