#include "Market.hpp"

int Market::count = 0;

Market::Market (string name, float x, float y)
    : location(x, y) {

    count++;
    this -> id = count;
    this -> name = name;
}

Market::Market (int id, string name, float x, float y)
    : location(x, y) {

    count = max(id, count+1);
    this -> id = id;
    this -> name = name;
}

Market::~Market () {}

bool Market::isAvailable (string name) const {

    try {
        findByName(name, this -> itemsForSale);
        return true;
    }
    catch (...) {
        return false;
    }
}

pair<float, Item*> Market::bestOffer (string name, Location location) const {

    float minCost = FLT_MAX, newCost;
    double distance = this -> getLocation().calculateDistance(location);
    Item* item = nullptr;

    for (auto it = itemsForSale.cbegin(); it < itemsForSale.cend(); it++) {
        if ((*it)->getName() == name) {
            newCost = (*it)->totalCost(distance);
            if (newCost < minCost) {
                minCost = newCost;
                item = *it;
            }
        }
    }
    return make_pair(minCost, item);
}

int Market::getId () const {

    return this -> id;
}

string Market::getName () const {

    return this -> name;
}

Location Market::getLocation () const {

    return this -> location;
}

void Market::insertItem (Item* item) {

    this -> itemsForSale.push_back(item);
}

bool Market::removeItem (Item* item) {

    return removeByValue(item, this -> itemsForSale);
}