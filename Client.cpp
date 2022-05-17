#include "Client.hpp"

void Client::canAfford (string name, Market* market) const {

    float cost = this -> checkPrice(name, market).first;
    if (this -> getMoney() < cost) {
        throw "Error: You cannot afford to purchase this item";
    }
}

Client::Client (size_t password, string name, float x, float y)
    : Person(password, name, x, y) {}

Client::Client (int id, size_t password, string name, float x, float y, float money)
    : Person(id, password, name, x, y, money) {}

Client::~Client () {}

pair<float, Item*> Client::purchaseFromMarket (string name, Market* market) {

    this -> canAfford(name, market);
    pair<float, Item*> pair = market -> bestOffer(name, this -> getLocation());
    
    market -> removeItem(pair.second);
    dynamic_cast<Salesman*>(pair.second->getSeller())->clearOffer(pair.second);
    dynamic_cast<Salesman*>(pair.second->getSeller())->finalizeOffer(pair.second);
    pair.second->setFinalCost(pair.first);
    pair.second->setBuyer(this);
    time_t now = time(nullptr);
    pair.second->setDate(ctime(&now));
    this -> money -= pair.first;
    this -> itemsPurchased.push_back(pair.second);
    return pair;
}

pair<float, Item*> Client::purchaseFromNearest (string name, const vector<Market*>& markets) {

    return this -> purchaseFromMarket(name, this -> nearestMarket(markets));
}

pair<float, Item*> Client::checkPrice (string name, Market* market) const {

    if (!market -> isAvailable(name)) {
        throw "Error: No offers for item with this name could be found on this market";
    }
    return market -> bestOffer(name, this -> getLocation());
}

pair<float, Item*> Client::checkNearest (string name, const vector<Market*>& markets) const {

    return this -> checkPrice(name, this -> nearestMarket(markets));
}

Market* Client::findCheapest (string name, const vector<Market*>& markets) const {

    float minCost = FLT_MAX, newCost;
    Market* market = nullptr;

    for (auto it = markets.cbegin(); it < markets.cend(); it++) {
        if ((*it)->isAvailable(name)) {
            newCost = (*it)->bestOffer(name, this -> getLocation()).first;
            if (newCost < minCost) {
                minCost = newCost;
                market = *it;
            }
        }
    }
    if (market) {
        return market;
    }
    throw "Error: No offers for item with this name could be found on any market";
}

bool Client::moneyDeposit (float amount) {

    if (amount < 0) {
        return false;
    }
    else {
        this -> money += amount;
        return true;
    }
}

void Client::transactionHistory () const {

    if (itemsPurchased.empty()) {
        cout << "No transactions were performed on this account" << endl;
    }
    else {
        for (auto it = itemsPurchased.cbegin(); it < itemsPurchased.cend(); it++) {
            (*it) -> showInfo(true);
        }
    }
}

void Client::insertPurchased (Item* item) {
    
    this -> itemsPurchased.push_back(item);
}