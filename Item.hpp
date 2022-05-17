#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

#include "Market.hpp"
#include "Person.hpp"

using namespace std;

class Market; // Forward Declarations
class Person;

class Item { // Abstract Class

    protected:

    static int count;
    int id;
    string name;
    string type;
    string date;
    float netCost;
    float finalCost;
    Market* market;
    Person* seller; // Salesman*
    Person* buyer; // Client*

    public:

    Item (string, string, float);

    Item (int, string, string, string, float, float, Market*, Person*, Person*);

    virtual ~Item ();

    virtual float totalCost (double) = 0;

    int getId () const;

    string getName () const;

    string getType () const;

    string getDate () const;

    float getNetCost () const;

    float getFinalCost () const;

    Market* getMarket () const;

    Person* getSeller () const;

    Person* getBuyer () const;

    virtual void showInfo (bool) const;

    void setDate (string);

    void setFinalCost (float);

    void setMarket (Market*);

    void setSeller (Person*);

    void setBuyer (Person*);

};

#endif