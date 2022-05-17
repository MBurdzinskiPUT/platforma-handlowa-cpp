#include "Salesman.hpp"

Salesman::Salesman (size_t password, string name, float x, float y)
    : Person(password, name, x, y) {}

Salesman::Salesman (int id, size_t password, string name, float x, float y, float money)
    : Person(id, password, name, x, y, money) {}

Salesman::~Salesman () {}

void Salesman::offerOnMarket (Item* item, Market* market) {

    market -> insertItem(item);
    item -> setMarket(market);
    item -> setSeller(this);
    this -> insertForSale(item);
}

void Salesman::offerOnNearest (Item* item, const vector<Market*>& markets) {

    this -> offerOnMarket(item, this -> nearestMarket(markets));
}

string Salesman::retractOffer (int id) {

    Item* item = findById(id, this -> itemsForSale);
    Market* market = item -> getMarket();
    if (!market) {
        throw "Error: This item does not have a market associated with it";
    }
    this -> clearOffer(item);
    market -> removeItem(item);
    item -> setMarket(nullptr);
    item -> setSeller(nullptr);
    return market -> getName();
}

void Salesman::activeOffers () const {

    if (itemsForSale.empty()) {
        cout << "There are no active offers to show" << endl;
    }
    else {
        for (auto it = itemsForSale.cbegin(); it < itemsForSale.cend(); it++) {
            (*it) -> showInfo(false);
        }
    }
}

bool Salesman::moneyWithdraw (float amount) {

    if (amount > (this -> money) || amount < 0) {
        return false;
    }
    else {
        this -> money -= amount;
        return true;
    }
}

void Salesman::transactionHistory () const {

    if (itemsSold.empty()) {
        cout << "No transactions were performed on this account" << endl;
    }
    else {
        for (auto it = itemsSold.cbegin(); it < itemsSold.cend(); it++) {
            (*it) -> showInfo(true);
        }
    }
}

bool Salesman::noOffers () const {

    return this -> itemsForSale.empty();
}

bool Salesman::clearOffer (Item* item) {

    return removeByValue(item, this -> itemsForSale);
}

void Salesman::insertForSale (Item* item) {

    this -> itemsForSale.push_back(item);
}

void Salesman::insertSold (Item* item) {
    
    this -> itemsSold.push_back(item);
}

void Salesman::finalizeOffer (Item* item) {

    this -> insertSold(item);
    this -> money += item -> getNetCost();
}