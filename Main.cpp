#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <ctype.h>
#include <float.h>

#include "Salesman.hpp"
#include "Client.hpp"
#include "Chattel.hpp"
#include "Estate.hpp"
#include "Validation.hpp"
#include "Context.hpp"
#include "Utility.hpp"
#include "Files.hpp"
#include "Encryption.hpp"

using namespace std;
using std::getline;

void viewOptions (const Context& activeContext) {

    switch (activeContext) {

        case MAIN:
            cout << "Main Menu" << endl;
            cout << "1 - Register a new salesman account" << endl;
            cout << "2 - Register a new client account" << endl;
            cout << "3 - Login to an existing salesman account" << endl;
            cout << "4 - Login to an existing client account" << endl;
            cout << "5 - Exit the application" << endl;
        break;

        case MENU_SM:
            cout << "Salesman Account Menu" << endl;
            cout << "1 - Create a new sale offer" << endl;
            cout << "2 - Show your active sale offers" << endl;
            cout << "3 - Retract an active sale offer" << endl;
            cout << "4 - Show account information" << endl;
            cout << "5 - Change account information" << endl;
            cout << "6 - Show account transaction history" << endl;
            cout << "7 - Withdraw money from your account" << endl;
            cout << "8 - Logout and return to the main menu" << endl;
        break;

        case MENU_CL:
            cout << "Client Account Menu" << endl;
            cout << "1 - Purchase an item from a market" << endl;
            cout << "2 - Check price of an item on a market" << endl;
            cout << "3 - Find the cheapest offer for an item" << endl;
            cout << "4 - Show account information" << endl;
            cout << "5 - Change account information" << endl;
            cout << "6 - Show account transaction history" << endl;
            cout << "7 - Deposit money on your account" << endl;
            cout << "8 - Logout and return to the main menu" << endl;
        break;

        default:
            cout << "Error: Program is in an invalid state" << endl;
        break;
    }
}

bool processOptions (Context& activeContext, Person*& loggedUser) {

    cout << "Choose one of the available options: ";
    string in;
    getline(cin, in);
    try {
        switch (activeContext) {

            case MAIN:
                switch (stoi(in)) {

                    case 1:
                        activeContext = REG_SM;
                        return true;
                    break;
                    case 2:
                        activeContext = REG_CL;
                        return true;
                    break;
                    case 3:
                        activeContext = LOG_SM;
                        return true;
                    break;
                    case 4:
                        activeContext = LOG_CL;
                        return true;
                    break;
                    case 5:
                        activeContext = EXIT;
                        return false;
                    break;
                    default:
                        cout << "Error: Please choose an existing option" << endl;
                        return false;
                    break;
                }
            break;

            case MENU_SM:
                switch (stoi(in)) {

                    case 1:
                        activeContext = SELL;
                        return true;
                    break;
                    case 2:
                        dynamic_cast<Salesman*>(loggedUser)->activeOffers();
                        return false;
                    break;
                    case 3:
                        activeContext = RETRACT;
                        return true;
                    break;
                    case 4:
                        dynamic_cast<Salesman*>(loggedUser)->showInfo();
                        return false;
                    break;
                    case 5:
                        activeContext = CHNG_SM;
                        return true;
                    break;
                    case 6:
                        dynamic_cast<Salesman*>(loggedUser)->transactionHistory();
                        return false;
                    break;
                    case 7:
                        activeContext = MON_SM;
                        return true;
                    break;
                    case 8:
                        loggedUser = nullptr;
                        activeContext = MAIN;
                        return false;
                    break;
                    default:
                        cout << "Error: Please choose an existing option" << endl;
                        return false;
                    break;
                }
            break;

            case MENU_CL:
                switch (stoi(in)) {
                    
                    case 1:
                        activeContext = BUY;
                        return true;
                    break;
                    case 2:
                        activeContext = CHECK;
                        return true;
                    break;
                    case 3:
                        activeContext = FIND;
                        return true;
                    break;
                    case 4:
                        dynamic_cast<Client*>(loggedUser)->showInfo();
                        return false;
                    break;
                    case 5:
                        activeContext = CHNG_CL;
                        return true;
                    break;
                    case 6:
                        dynamic_cast<Client*>(loggedUser)->transactionHistory();
                        return false;
                    break;
                    case 7:
                        activeContext = MON_CL;
                        return true;
                    break;
                    case 8:
                        loggedUser = nullptr;
                        activeContext = MAIN;
                        return false;
                    break;
                    default:
                        cout << "Error: Please choose an existing option" << endl;
                        return false;
                    break;
                }
            break;

            default:
                cout << "Error: Program is in an invalid state" << endl;
                return false;
            break;
        }
    }
    catch (...) {
        cout << "Error: Please provide a valid integer value" << endl;
        return false;
    }
}

void inputData (Context& activeContext, Person*& loggedUser, vector<Market*>& markets, vector<Salesman*>& salesmen, vector<Client*>& clients, vector<Item*>& items) {

    string in[4];
    Person* user;
    Item* item;
    string fileName;

    switch (activeContext) {

        case REG_SM:
        case REG_CL:
            while (true) {
                cout << "Choose the username for your account: ";
                getline(cin, in[0]);
                try {
                    validateUsername(in[0], activeContext, salesmen, clients);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            while (true) {
                cout << "Type in your password (at least 8 characters): ";
                getline(cin, in[1]);
                try {
                    validatePassword(in[1]);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            while (true) {
                cout << "Provide the X coordinate of your location (number between -180 and 180): ";
                getline(cin, in[2]);
                try {
                    validateX(in[2]);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            while (true) {
                cout << "Provide the Y coordinate of your location (number between -90 and 90): ";
                getline(cin, in[3]);
                try {
                    validateY(in[3]);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }          
            if (activeContext == REG_SM) {
                salesmen.push_back(new Salesman(rshash(in[1]), in[0], stof(in[2]), stof(in[3])));
                loggedUser = salesmen.back();
                fileName = "Data/Salesmen.txt";
                activeContext = MENU_SM;
            }
            else { // activeContext == REG_CL
                clients.push_back(new Client(rshash(in[1]), in[0], stof(in[2]), stof(in[3])));
                loggedUser = clients.back();
                fileName = "Data/Clients.txt";
                activeContext = MENU_CL;
            }
            try {
                insertToFile(fileName, loggedUser, nullptr);
            }
            catch (...) {
                cout << "Error: Account data could not be saved to file" << endl;
            }
            cout << "Account registered successfully" << endl;
        break;

        case LOG_SM:
        case LOG_CL:
            cout << "Username: ";
            getline(cin, in[0]);
            if (activeContext == LOG_SM) {
                try {
                    user = findByName(in[0], salesmen);
                }
                catch (...) {
                    cout << "Error: Salesman account with this username was not found" << endl;
                    activeContext = MAIN;
                    break;
                }
            }
            else { // activeContext == LOG_CL
                try {
                    user = findByName(in[0], clients);
                }
                catch (...) {
                    cout << "Error: Client account with this username was not found" << endl;
                    activeContext = MAIN;
                    break;
                }
            }
            cout << "Password: ";
            getline(cin, in[1]);
            if (user -> getPassword() != rshash(in[1])) {
                cout << "Error: Passwords do not match" << endl;
                activeContext = MAIN;
                break;
            }
            loggedUser = user;
            if (activeContext == LOG_SM) {
                activeContext = MENU_SM;
            }
            else { // activeContext == LOG_CL
                activeContext = MENU_CL;
            }
            cout << "Logged in successfully" << endl;
        break;

        case MON_SM:
            { float money = dynamic_cast<Salesman*>(loggedUser)->getMoney();
            if (money == 0) {
                cout << "Error: There is no money to withdraw from the account" << endl;
                activeContext = MENU_SM;
                break;
            }
            while (true) {
                cout << "Choose the amount of money to withdraw (" << money << " units available): ";
                getline(cin, in[0]);
                try {
                    if (dynamic_cast<Salesman*>(loggedUser)->moneyWithdraw(stof(in[0]))) {
                        break;
                    }
                    else {
                        throw "";
                    }
                }
                catch (...) {
                    cout << "Error: The amount of money must be a number between 0 and " << money << endl;
                }
            } }
            fileName = "Data/Salesmen.txt";
            try {
                updateInFile(fileName, loggedUser, nullptr);
            }
            catch (...) {
                cout << "Error: Account data could not be saved to file" << endl;
            }
            cout << "Account balance decreased to " << dynamic_cast<Salesman*>(loggedUser)->getMoney() << endl;
            activeContext = MENU_SM;
        break;

        case MON_CL:
            while (true) {
                cout << "Choose the amount of money to deposit: ";
                getline(cin, in[0]);
                try {
                    if (dynamic_cast<Client*>(loggedUser)->moneyDeposit(stof(in[0]))) {
                        break;
                    }
                    else {
                        throw "";
                    }
                }
                catch (...) {
                    cout << "Error: The amount of money must be a number greater than 0" << endl;
                }
            }
            fileName = "Data/Clients.txt";
            try {
                updateInFile(fileName, loggedUser, nullptr);
            }
            catch (...) {
                cout << "Error: Account data could not be saved to file" << endl;
            }
            cout << "Account balance increased to " << dynamic_cast<Client*>(loggedUser)->getMoney() << endl;
            activeContext = MENU_CL;
        break;

        case CHNG_SM:
        case CHNG_CL:
            cout << "Leaving a field blank will keep current account information" << endl;
            while (true) {
                cout << "Choose the new username for your account: ";
                getline(cin, in[0]);
                if (in[0].empty()) {
                    break;
                }
                try {
                    validateUsername(in[0], activeContext, salesmen, clients);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            while (true) {
                cout << "Type in your new password (at least 8 characters): ";
                getline(cin, in[1]);
                if (in[1].empty()) {
                    break;
                }
                try {
                    validatePassword(in[1]);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            while (true) {
                cout << "Provide the X coordinate of your new location (number between -180 and 180): ";
                getline(cin, in[2]);
                if (in[2].empty()) {
                    break;
                }
                try {
                    validateX(in[2]);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            while (true) {
                cout << "Provide the Y coordinate of your new location (number between -90 and 90): ";
                getline(cin, in[3]);
                if (in[3].empty()) {
                    break;
                }
                try {
                    validateY(in[3]);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            if (!in[0].empty()) {
                loggedUser->setName(in[0]);
            }
            if (!in[1].empty()) {
                loggedUser->setPassword(rshash(in[1]));
            }
            if (!in[2].empty()) {
                loggedUser->setX(stof(in[2]));
            }
            if (!in[3].empty()) {
                loggedUser->setY(stof(in[3]));
            }
            if (activeContext == CHNG_SM) {
                fileName = "Data/Salesmen.txt";
            }
            else { // activeContext == CHNG_CL
                fileName = "Data/Clients.txt";
            }
            try {
                updateInFile(fileName, loggedUser, nullptr);
            }
            catch (...) {
                cout << "Error: Account data could not be saved to file" << endl;
            }
            cout << "Information updated successfully" << endl;
            if (activeContext == CHNG_SM) {
                activeContext = MENU_SM;
            }
            else { // activeContext == CHNG_CL
                activeContext = MENU_CL;
            }
        break;

        case SELL:
            while (true) {
                cout << "Enter the name of the item you want to sell: ";
                getline(cin, in[0]);
                try {
                    validateName(in[0]);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            while (true) {
                cout << "Choose the net price of the item: ";
                getline(cin, in[1]);
                try {
                    validateFloat(in[1]);
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            while (true) {
                cout << "Is this item a chattel or an estate? Type in 'c' or 'e': ";
                getline(cin, in[2]);
                if (in[2] == "c") {
                    while (true) {
                        cout << "Enter the delivery cost multiplier: ";
                        getline(cin, in[3]);
                        try {
                            validateFloat(in[3]);
                            break;
                        }
                        catch (const char* error) {
                            cout << error << endl;
                        }
                    }
                    items.push_back(new Chattel(in[0], stof(in[1]), stof(in[3])));
                    item = items.back();
                    break;
                }
                else if (in[2] == "e") {
                    while (true) {
                        cout << "Enter the property tax value (in percents): ";
                        getline(cin, in[3]);
                        try {
                            validateFloat(in[3]);
                            break;
                        }
                        catch (const char* error) {
                            cout << error << endl;
                        }
                    }
                    items.push_back(new Estate(in[0], stof(in[1]), stof(in[3]) / 100));
                    item = items.back();
                    break;
                }
                else {
                    cout << "Error: Neither item category was chosen" << endl;
                }
            }
            while (true) {
                cout << "Provide the name of the market to sell the item or leave blank for nearest: ";
                getline(cin, in[2]);
                if (in[2].empty()) {
                    try {
                        dynamic_cast<Salesman*>(loggedUser)->offerOnNearest(item, markets);
                        break;
                    }
                    catch (const char* error) {
                        cout << error << endl;
                    }
                }
                else {
                    try {
                        dynamic_cast<Salesman*>(loggedUser)->offerOnMarket(item, findByName(in[2], markets));
                        break;
                    }
                    catch (const char* error) {
                        cout << error << endl;
                    }
                }
            }
            fileName = "Data/Items.txt";
            try {
                insertToFile(fileName, nullptr, item);
            }
            catch (...) {
                cout << "Error: Item data could not be saved to file" << endl;
            }
            cout << "Item successfully offered on " << item -> getMarket() -> getName() << endl;
            activeContext = MENU_SM;
        break;

        case RETRACT:
            if (dynamic_cast<Salesman*>(loggedUser)->noOffers()) {
                cout << "Error: There are no active offers to retract" << endl;
                activeContext = MENU_SM;
                break;
            }
            while (true) {
                cout << "Provide the ID of the item you wish to retract or leave blank to cancel: ";
                getline(cin, in[0]);
                if (in[0].empty()) {
                    cout << "Operation cancelled" << endl;
                    break;
                }
                try {
                    validateInt(in[0]);
                    string name = dynamic_cast<Salesman*>(loggedUser)->retractOffer(stoi(in[0]));
                    cout << "Item retracted successfully from " << name << endl;
                    break;
                }
                catch (const char* error) {
                    cout << error << endl;
                }
            }
            if (!in[0].empty()) {
                fileName = "Data/Items.txt";
                try {
                    removeFromFile(fileName, nullptr, stoi(in[0]));
                }
                catch (...) {
                    cout << "Error: Item data could not be saved to file" << endl;
                }
            }
            activeContext = MENU_SM;
        break;

        case BUY:
            { pair<float, Item*> pair;
            cout << "Enter the name of the item you want to purchase: ";
            getline(cin, in[0]);
            cout << "Enter the name of the market to purchase from or leave blank for nearest: ";
            getline(cin, in[1]);
            try {
                if (in[1].empty()) {
                    pair = dynamic_cast<Client*>(loggedUser)->purchaseFromNearest(in[0], markets);
                }
                else {
                    pair = dynamic_cast<Client*>(loggedUser)->purchaseFromMarket(in[0], findByName(in[1], markets));
                }
            }
            catch (const char* error) {
                cout << error << endl;
                activeContext = MENU_CL;
                break;
            }
            try {
                fileName = "Data/Salesmen.txt";
                updateInFile(fileName, pair.second -> getSeller(), nullptr);
                fileName = "Data/Clients.txt";
                updateInFile(fileName, loggedUser, nullptr);
            }
            catch (...) {
                cout << "Error: Account data could not be saved to file" << endl;
            }
            try {
                fileName = "Data/Items.txt";
                updateInFile(fileName, nullptr, pair.second);
            }
            catch (...) {
                cout << "Error: Item data could not be saved to file" << endl;
            }
            cout << "Successfully purchased " << in[0] << " for " << pair.first << " from " << pair.second -> getMarket() -> getName() << endl;
            activeContext = MENU_CL;
            }
        break;

        case CHECK:
            { pair<float, Item*> pair;
            cout << "Enter the name of the item you want to check price of: ";
            getline(cin, in[0]);
            cout << "Enter the name of the market to search on or leave blank for nearest: ";
            getline(cin, in[1]);
            try {
                if (in[1].empty()) {
                    pair = dynamic_cast<Client*>(loggedUser)->checkNearest(in[0], markets);
                }
                else {
                    pair = dynamic_cast<Client*>(loggedUser)->checkPrice(in[0], findByName(in[1], markets));
                }
            }
            catch (const char* error) {
                cout << error << endl;
                activeContext = MENU_CL;
                break;
            }
            cout << in[0] << " costs " << pair.first << " on " << pair.second -> getMarket() -> getName() << endl;
            activeContext = MENU_CL;
            }
        break;

        case FIND:
            { pair<float, Item*> pair;
            cout << "Enter the name of the item to search for cheapest offers: ";
            getline(cin, in[0]);
            try {
                pair = dynamic_cast<Client*>(loggedUser)->checkPrice(in[0], dynamic_cast<Client*>(loggedUser)->findCheapest(in[0], markets));
            }
            catch (const char* error) {
                cout << error << endl;
                activeContext = MENU_CL;
                break;
            }
            cout << "Best offer for " << in[0] << " is " << pair.first << " on " << pair.second -> getMarket() -> getName() << endl;
            activeContext = MENU_CL;
            }
        break;

        default:
            cout << "Error: Program is in an invalid state" << endl;
        break;
    }
}

int main (int argc, char* argv[]) {

    vector<Market*> markets;
    vector<Salesman*> salesmen;
    vector<Client*> clients;
    vector<Item*> items;

    ifstream inFile;
    ofstream outFile;
    string fileName;
    
    fileName = "Data/Marketplaces.txt";
    inFile.open(fileName);
    if (!inFile.good()) {
        cout << "Fatal Error: The program was unable to open the database file: " << fileName << endl;
        cout << "Enter any value to terminate the application: ";
        cin >> fileName;
        return 1;
    }
    string in[10];
    getline(inFile, in[0]);
    try {
        int n = stoi(in[0]);
        if (n < 1) {
            throw "";
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                getline(inFile, in[j]);
            }
            markets.push_back(new Market(stoi(in[0]), in[1], stoi(in[2]), stoi(in[3])));
        }
    }
    catch (...) {
        cout << "Fatal Error: The database file is corrupted: " << fileName << endl;
        cout << "Enter any value to terminate the application: ";
        cin >> fileName;
        return 2;
    }
    inFile.close();

    fileName = "Data/Salesmen.txt";
    inFile.open(fileName);
    if (!inFile.good()) {
        cout << "No existing salesman account data detected" << endl;
        outFile.open(fileName);
        if (!outFile.good()) {
            cout << "Error: Opening " << fileName << " failed" << endl;
        }
        else {
            outFile << encrypt(to_string(0)) << endl;
        }
        outFile.close();
    }
    else {
        getline(inFile, in[0]);
        in[0] = decrypt(in[0]);
        try {
            int n = stoi(in[0]);
            if (n < 0) {
                throw "";
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 6; j++) {
                    getline(inFile, in[j]);
                    in[j] = decrypt(in[j]);
                }
                salesmen.push_back(new Salesman(stoi(in[0]), stoull(in[1]), in[2], stof(in[3]), stof(in[4]), stof(in[5])));
            }
        }
        catch (...) {
            cout << "Error: The file is corrupted: " << fileName << endl;
            cout << "Some information might have been lost" << endl;
        }
    }
    inFile.close();

    fileName = "Data/Clients.txt";
    inFile.open(fileName);
    if (!inFile.good()) {
        cout << "No existing client account data detected" << endl;
        outFile.open(fileName);
        if (!outFile.good()) {
            cout << "Error: Opening " << fileName << " failed" << endl;
        }
        else {
            outFile << encrypt(to_string(0)) << endl;
        }
        outFile.close();
    }
    else {
        getline(inFile, in[0]);
        in[0] = decrypt(in[0]);
        try {
            int n = stoi(in[0]);
            if (n < 0) {
                throw "";
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 6; j++) {
                    getline(inFile, in[j]);
                    in[j] = decrypt(in[j]);
                }
                clients.push_back(new Client(stoi(in[0]), stoull(in[1]), in[2], stof(in[3]), stof(in[4]), stof(in[5])));
            }
        }
        catch (...) {
            cout << "Error: The file is corrupted: " << fileName << endl;
            cout << "Some information might have been lost" << endl;
        }
    }
    inFile.close();

    fileName = "Data/Items.txt";
    inFile.open(fileName);
    if (!inFile.good()) {
        cout << "No existing item data detected" << endl;
        outFile.open(fileName);
        if (!outFile.good()) {
            cout << "Error: Opening " << fileName << " failed" << endl;
        }
        else {
            outFile << encrypt(to_string(0)) << endl;
        }
        outFile.close();
    }
    else {
        getline(inFile, in[0]);
        in[0] = decrypt(in[0]);
        try {
            int n = stoi(in[0]);
            if (n < 0) {
                throw "";
            }
            Market* market;
            Salesman* seller;
            Client* buyer;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 10; j++) {
                    getline(inFile, in[j]);
                    in[j] = decrypt(in[j]);
                }
                try {
                    market = findById(stoi(in[6]), markets);
                }
                catch (...) {
                    market = nullptr;
                }
                try {
                    seller = findById(stoi(in[7]), salesmen);
                }
                catch (...) {
                    seller = nullptr;
                }
                try {
                    buyer = findById(stoi(in[8]), clients);
                }
                catch (...) {
                    buyer = nullptr;
                }
                if (in[2] == "Chattel") {
                    items.push_back(new Chattel(stoi(in[0]), in[1], in[3], stof(in[4]), stof(in[5]), market, seller, buyer, stof(in[9])));
                }
                else { // in[2] == "Estate"
                    items.push_back(new Estate(stoi(in[0]), in[1], in[3], stof(in[4]), stof(in[5]), market, seller, buyer, stof(in[9])));
                }
                if (buyer) { // Sold
                    buyer -> insertPurchased(items.back());
                    seller -> insertSold(items.back());
                }
                else { // Not Sold
                    market -> insertItem(items.back());
                    seller -> insertForSale(items.back());    
                }
            }
        }
        catch (...) {
            cout << "Error: The file is corrupted: " << fileName << endl;
            cout << "Some information might have been lost" << endl;
        }
    }
    inFile.close();

    Context activeContext = MAIN;
    bool inputRequired = false;
    Person* loggedUser = nullptr;

    while (activeContext != EXIT) {
        cout << string(50, '=') << endl;
        if (inputRequired) {
            inputData(activeContext, loggedUser, markets, salesmen, clients, items);
            cout << string(50, '=') << endl;
        }
        viewOptions(activeContext);
        inputRequired = processOptions(activeContext, loggedUser);
    }

    while (!markets.empty()) {
        delete markets.back();
        markets.pop_back();
    }
    while (!salesmen.empty()) {
        delete salesmen.back();
        salesmen.pop_back();
    }
    while (!clients.empty()) {
        delete clients.back();
        clients.pop_back();
    }
    while (!items.empty()) {
        delete items.back();
        items.pop_back();
    }

    return 0;
}