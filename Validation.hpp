#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include <string>
#include <vector>
#include <algorithm>

#include "Salesman.hpp"
#include "Client.hpp"
#include "Context.hpp"

using namespace std;

void validateUsername (const string&, const Context&, vector<Salesman*>&, vector<Client*>&);

void validatePassword (const string&);

void validateX (const string&);

void validateY (const string&);

void validateName (const string&);

void validateFloat (const string&);

void validateInt (const string&);

#endif