#include "Validation.hpp"

void validateUsername (const string& name, const Context& activeContext, vector<Salesman*>& salesmen, vector<Client*>& clients) {

    Person* user = nullptr;
    if (all_of(name.begin(), name.end(), ::isspace)) {
        throw "Error: The username must contain visible characters";
    }
    if (activeContext == REG_SM || activeContext == CHNG_SM) {
        try {
            user = findByName(name, salesmen);
        }
        catch (...) {
            // Not Found = Ok
        }
        if (user) {
            throw "Error: A salesman account with this name already exists";
        }
    }
    else { // activeContext == REG_CL || activeContext == CHNG_CL 
        try {
            user = findByName(name, clients);
        }
        catch (...) {
            // Not Found = Ok
        }
        if (user) {
            throw "Error: A client account with this name already exists";
        }
    }
}

void validatePassword (const string& password) {

    if (password.size() < 8) {
        throw "Error: The password must contain at least 8 characters";
    }
    if (all_of(password.begin(), password.end(), ::isspace)) {
        throw "Error: The password must contain visible characters";
    }
}

void validateX (const string& sx) {

    float x;
    try {
        x = stof(sx);
    }
    catch (...) {
        throw "Error: The X coordinate must be a floating point number";
    }
    if (x < -180 || x > 180) {
        throw "Error: The X coordinate must be between -180 and 180";
    }
}

void validateY (const string& sy) {

    float y;
    try {
        y = stof(sy);
    }
    catch (...) {
        throw "Error: The Y coordinate must be a floating point number";
    }
    if (y < -90 || y > 90) {
        throw "Error: The Y coordinate must be between -90 and 90";
    }
}

void validateName (const string& name) {

    if (all_of(name.begin(), name.end(), ::isspace)) {
        throw "Error: The name of the item must contain visible characters";
    }
}

void validateFloat (const string& sf) {

    float f;
    try {
        f = stof(sf);
    }
    catch (...) {
        throw "Error: This value must be a floating point number";
    }
    if (f < 0) {
        throw "Error: This value must not be a negative number";
    }
}

void validateInt (const string& si) {

    int i;
    try {
        i = stoi(si);
    }
    catch (...) {
        throw "Error: This value must be an integer";
    }
    if (i < 0) {
        throw "Error: This value must not be a negative number";
    }
}