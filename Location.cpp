#include "Location.hpp"

double Location::toRadians (double degrees) const {

    return degrees * M_PI / 180;
}

Location::Location (float x, float y) {

    this -> x = x;
    this -> y = y;
}

Location::~Location () {}

double Location::calculateDistance (Location location) const {

    double radX[2] = {toRadians(this -> getX()), toRadians(location.getX())};
    double radY[2] = {toRadians(this -> getY()), toRadians(location.getY())};
    
    double haversine = pow(sin((radY[1] - radY[0]) / 2), 2) + cos(radY[0]) * cos(radY[1]) * pow(sin((radX[1] - radX[0]) / 2), 2);
    return diameter * asin(sqrt(haversine));
}

float Location::getX () const {

    return this -> x;
}

float Location::getY () const {

    return this -> y;
}

void Location::setX (float x) {

    this -> x = x;
}

void Location::setY (float y) {

    this -> y = y;
}