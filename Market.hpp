#ifndef MARKET_HPP
#define MARKET_HPP

#include <string>
#include <vector>
#include <utility>
#include <float.h>

#include "Location.hpp"
#include "Item.hpp"
#include "Utility.hpp"

using namespace std;

class Item; // Forward Declarations

class Market {

    static int count;
    int id;
    string name;
    Location location;
    vector<Item*> itemsForSale;

    public:

    Market (string, float, float);

    Market (int, string, float, float);

    ~Market ();

    bool isAvailable (string) const;

    pair<float, Item*> bestOffer (string, Location) const;

    int getId () const;

    string getName () const;

    Location getLocation () const;

    void insertItem (Item*);

    bool removeItem (Item*);

};

#endif