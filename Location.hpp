#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <math.h>

class Location {

    static constexpr int diameter = 12742;
    float x;
    float y;

    double toRadians (double) const;

    public:

    Location (float, float);

    ~Location ();

    double calculateDistance (Location) const;

    float getX () const;

    float getY () const;

    void setX (float);

    void setY (float);

};

#endif