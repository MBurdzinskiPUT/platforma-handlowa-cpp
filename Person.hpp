#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>
#include <vector>
#include <float.h>

#include "Location.hpp"
#include "Market.hpp"

using namespace std;

class Market; // Forward Declarations

class Person { // Abstract Class

    protected:

    static int count;
    int id;
    size_t password;
    string name;
    float money;
    Location location;

    Market* nearestMarket (const vector<Market*>&) const;

    public:

    Person (size_t, string, float, float);

    Person (int, size_t, string, float, float, float);

    virtual ~Person ();

    virtual void transactionHistory () const = 0;

    int getId () const;

    size_t getPassword () const;

    string getName () const;

    float getMoney () const;

    Location getLocation () const;

    virtual void showInfo () const;

    void setPassword (size_t);

    void setName (string);

    void setX (float);

    void setY (float);

};

#endif