#ifndef CHATTEL_HPP
#define CHATTEL_HPP

#include <math.h>

#include "Item.hpp"
#include "Taxed.hpp"

class Chattel: public Taxed, public Item {

    float deliveryCost;

    public:

    Chattel (string, float, float);

    Chattel (int, string, string, float, float, Market*, Person*, Person*, float);

    ~Chattel ();

    float calculateTax () override;

    float totalCost (double) override;

    float getDeliveryCost () const;

    void showInfo (bool) const override;

};

#endif