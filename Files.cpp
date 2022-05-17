#include "Files.hpp"

void copyFile (const string& source, const string& destination) {

    fstream sourceFile, destinationFile;
    string buffer;
    sourceFile.open(source, ios_base::in);
    destinationFile.open(destination, ios_base::out | ios_base::trunc);
    if (!sourceFile.good() || !destinationFile.good()) {
        throw "";
    }
    while (getline(sourceFile, buffer)) {
        destinationFile << buffer << endl;
    }
    sourceFile.close();
    destinationFile.close();
}

void insertToFile (const string& fileName, Person* loggedUser, Item* item) {

    fstream tempFile, realFile;
    string buffer;
    int fields;
    if (loggedUser) {
        fields = 6;
    }
    else { // item
        fields = 10;
    }
    tempFile.open("Data/Temporary.txt", ios_base::out | ios_base::trunc);
    realFile.open(fileName, ios_base::in);
    try {
        if (!tempFile.good() || !realFile.good()) {
            throw "";
        }
        getline(realFile, buffer);
        buffer = decrypt(buffer);
        int objects = stoi(buffer);
        tempFile << encrypt(to_string(objects+1)) << endl;
        for (int i = 0; i < objects; i++) {
            for (int j = 0; j < fields; j++) {
                getline(realFile, buffer);
                tempFile << buffer << endl;
            }
        }
        if (loggedUser) {
            tempFile << encrypt(to_string(loggedUser -> getId())) << endl;
            tempFile << encrypt(to_string(loggedUser -> getPassword())) << endl;
            tempFile << encrypt(loggedUser -> getName()) << endl;
            tempFile << encrypt(to_string(loggedUser -> getLocation().getX())) << endl;
            tempFile << encrypt(to_string(loggedUser -> getLocation().getY())) << endl;
            tempFile << encrypt(to_string(loggedUser -> getMoney())) << endl;
        }
        else { // item
            tempFile << encrypt(to_string(item -> getId())) << endl;
            tempFile << encrypt(item -> getName()) << endl;
            tempFile << encrypt(item -> getType()) << endl;
            tempFile << encrypt(item -> getDate()) << endl;
            tempFile << encrypt(to_string(item -> getNetCost())) << endl;
            tempFile << encrypt(to_string(item -> getFinalCost())) << endl;
            if (item -> getMarket()) {
                tempFile << encrypt(to_string(item -> getMarket() -> getId())) << endl;
            }
            else {
                tempFile << encrypt(to_string(0)) << endl;
            }
            if (item -> getSeller()) {
                tempFile << encrypt(to_string(item -> getSeller() -> getId())) << endl;
            }
            else {
                tempFile << encrypt(to_string(0)) << endl;
            }
            if (item -> getBuyer()) {
                tempFile << encrypt(to_string(item -> getBuyer() -> getId())) << endl;
            }
            else {
                tempFile << encrypt(to_string(0)) << endl;
            }
            if (item -> getType() == "Chattel") {
                tempFile << encrypt(to_string(dynamic_cast<Chattel*>(item)->getDeliveryCost())) << endl;
            }
            else { // item -> getType() == "Estate"
                tempFile << encrypt(to_string(dynamic_cast<Estate*>(item)->getPropertyTax())) << endl;
            }
        }
        tempFile.close();
        realFile.close();
        copyFile("Data/Temporary.txt", fileName);
    }
    catch (...) {
        remove("Data/Temporary.txt");
        throw;
    }
    remove("Data/Temporary.txt");
}

void updateInFile (const string& fileName, Person* loggedUser, Item* item) {

    fstream tempFile, realFile;
    string buffer;
    int fields, id;
    if (loggedUser) {
        fields = 6;
    }
    else { // item
        fields = 10;
    }
    tempFile.open("Data/Temporary.txt", ios_base::out | ios_base::trunc);
    realFile.open(fileName, ios_base::in);
    try {
        if (!tempFile.good() || !realFile.good()) {
            throw "";
        }
        if (loggedUser) {
            id = loggedUser -> getId();
        }
        else { // item
            id = item -> getId();
        }
        getline(realFile, buffer);
        buffer = decrypt(buffer);
        int objects = stoi(buffer);
        tempFile << encrypt(to_string(objects)) << endl;
        for (int i = 0; i < objects; i++) {
            for (int j = 0; j < fields; j++) {
                getline(realFile, buffer);
                buffer = decrypt(buffer);
                if (j == 0 && stoi(buffer) == id) { // Found
                    if (loggedUser) {
                        tempFile << encrypt(to_string(loggedUser -> getId())) << endl;
                        tempFile << encrypt(to_string(loggedUser -> getPassword())) << endl;
                        tempFile << encrypt(loggedUser -> getName()) << endl;
                        tempFile << encrypt(to_string(loggedUser -> getLocation().getX())) << endl;
                        tempFile << encrypt(to_string(loggedUser -> getLocation().getY())) << endl;
                        tempFile << encrypt(to_string(loggedUser -> getMoney())) << endl;
                    }
                    else { // item
                        tempFile << encrypt(to_string(item -> getId())) << endl;
                        tempFile << encrypt(item -> getName()) << endl;
                        tempFile << encrypt(item -> getType()) << endl;
                        tempFile << encrypt(item -> getDate()) << endl;
                        tempFile << encrypt(to_string(item -> getNetCost())) << endl;
                        tempFile << encrypt(to_string(item -> getFinalCost())) << endl;
                        if (item -> getMarket()) {
                            tempFile << encrypt(to_string(item -> getMarket() -> getId())) << endl;
                        }
                        else {
                            tempFile << encrypt(to_string(0)) << endl;
                        }
                        if (item -> getSeller()) {
                            tempFile << encrypt(to_string(item -> getSeller() -> getId())) << endl;
                        }
                        else {
                            tempFile << encrypt(to_string(0)) << endl;
                        }
                        if (item -> getBuyer()) {
                            tempFile << encrypt(to_string(item -> getBuyer() -> getId())) << endl;
                        }
                        else {
                            tempFile << encrypt(to_string(0)) << endl;
                        }
                        if (item -> getType() == "Chattel") {
                            tempFile << encrypt(to_string(dynamic_cast<Chattel*>(item)->getDeliveryCost())) << endl;
                        }
                        else { // item -> getType() == "Estate"
                            tempFile << encrypt(to_string(dynamic_cast<Estate*>(item)->getPropertyTax())) << endl;
                        }
                    }
                    for (int k = 0; k < fields-1; k++) { // Skip
                        getline(realFile, buffer);
                    }
                    break;
                }
                else {
                    tempFile << encrypt(buffer) << endl;
                }
            }
        }
        tempFile.close();
        realFile.close();
        copyFile("Data/Temporary.txt", fileName);
    }
    catch (...) {
        remove("Data/Temporary.txt");
        throw;
    }
    remove("Data/Temporary.txt");
}

void removeFromFile (const string& fileName, Person* loggedUser, int id) {

    fstream tempFile, realFile;
    string buffer;
    int fields;
    if (loggedUser) {
        fields = 6;
    }
    else { // item
        fields = 10;
    }
    tempFile.open("Data/Temporary.txt", ios_base::out | ios_base::trunc);  
    realFile.open(fileName, ios_base::in);
    try {
        if (!tempFile.good() || !realFile.good()) {
            throw "";
        }
        getline(realFile, buffer);
        buffer = decrypt(buffer);
        int objects = stoi(buffer);
        tempFile << encrypt(to_string(objects-1)) << endl;
        for (int i = 0; i < objects; i++) {
            for (int j = 0; j < fields; j++) {
                getline(realFile, buffer);
                buffer = decrypt(buffer);
                if (j == 0 && stoi(buffer) == id) {
                    for (int k = 0; k < fields-1; k++) { // Skip
                        getline(realFile, buffer);
                    }
                    break;
                }
                else {
                    tempFile << encrypt(buffer) << endl;
                }
            }
        }
        tempFile.close();
        realFile.close();
        copyFile("Data/Temporary.txt", fileName);
    }
    catch (...) {
        remove("Data/Temporary.txt");
        throw;
    }
    remove("Data/Temporary.txt");
}