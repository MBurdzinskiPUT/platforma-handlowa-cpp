#ifndef SALESMAN_HPP
#define SALESMAN_HPP

#include <string>
#include <vector>

#include "Person.hpp"
#include "Market.hpp"
#include "Item.hpp"

using namespace std;

class Salesman: public Person {

    vector<Item*> itemsForSale;
    vector<Item*> itemsSold;

    public:

    Salesman (size_t, string, float, float);

    Salesman (int, size_t, string, float, float, float);

    ~Salesman ();

    void offerOnMarket (Item*, Market*);

    void offerOnNearest (Item*, const vector<Market*>&);

    string retractOffer (int);
    
    void activeOffers () const;

    bool moneyWithdraw (float);

    void transactionHistory () const override;

    bool noOffers () const;

    bool clearOffer (Item*);

    void insertForSale (Item*);

    void insertSold (Item*);

    void finalizeOffer (Item*);

};

#endif