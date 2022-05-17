#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <utility>
#include <time.h>

#include "Person.hpp"
#include "Market.hpp"
#include "Item.hpp"
#include "Salesman.hpp"

using namespace std;

class Client: public Person {

    vector<Item*> itemsPurchased;

    void canAfford (string, Market*) const;

    public:

    Client (size_t, string, float, float);

    Client (int, size_t, string, float, float, float);

    ~Client ();

    pair<float, Item*> purchaseFromMarket (string, Market*);

    pair<float, Item*> purchaseFromNearest (string, const vector<Market*>&);

    pair<float, Item*> checkPrice (string, Market*) const;

    pair<float, Item*> checkNearest (string, const vector<Market*>&) const;

    Market* findCheapest (string, const vector<Market*>&) const;

    bool moneyDeposit (float);

    void transactionHistory () const override;

    void insertPurchased (Item*);

};

#endif