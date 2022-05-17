#ifndef ESTATE_HPP
#define ESTATE_HPP

#include "Item.hpp"
#include "Taxed.hpp"

class Estate: public Taxed, public Item {

    float propertyTax;

    public:

    Estate (string, float, float);

    Estate (int, string, string, float, float, Market*, Person*, Person*, float);

    ~Estate ();

    float calculateTax () override;

    float totalCost (double) override;

    float getPropertyTax () const;

    void showInfo (bool) const override;

};

#endif