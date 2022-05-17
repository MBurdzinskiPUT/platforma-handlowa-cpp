#include "Person.hpp"

int Person::count = 0;

Market* Person::nearestMarket (const vector<Market*>& markets) const {

    double minDistance = DBL_MAX, newDistance;
    Market* market = nullptr;

    for (auto it = markets.cbegin(); it < markets.cend(); it++) {
        newDistance = this -> getLocation().calculateDistance((*it)->getLocation());
        if (newDistance < minDistance) {
            minDistance = newDistance;
            market = *it;
        }
    }
    if (market) {
        return market;
    }
    throw "Error: Nearest market could not be found";
}

Person::Person (size_t password, string name, float x, float y)
    : location(x, y) {

    count++;
    this -> id = count;
    this -> password = password;
    this -> name = name;
    this -> money = 0;
}

Person::Person (int id, size_t password, string name, float x, float y, float money)
    : location(x, y) {

    count = max(id, count+1);
    this -> id = id;
    this -> password = password;
    this -> name = name;
    this -> money = money;
}

Person::~Person () {}

int Person::getId () const {

    return this -> id;
}

size_t Person::getPassword () const {

    return this -> password;
}

string Person::getName () const {

    return this -> name;
}

float Person::getMoney () const {

    return this -> money;
}

Location Person::getLocation () const {

    return this -> location;
}

void Person::showInfo () const {

    Location location = this -> getLocation();
    cout << "Username: " + this -> getName() << endl;
    cout << "Balance: " + to_string(this -> getMoney()) << endl;
    cout << "Location (X, Y): " + to_string(location.getX()) + ", " + to_string(location.getY()) << endl;
}

void Person::setPassword (size_t password) {

    this -> password = password;
}

void Person::setName (string name) {

    this -> name = name;
}

void Person::setX (float x) {

    this -> location.setX(x);
}

void Person::setY (float y) {

    this -> location.setY(y);
}