#ifndef FILES_HPP
#define FILES_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "Person.hpp"
#include "Chattel.hpp"
#include "Estate.hpp"
#include "Encryption.hpp"

using namespace std;
using std::getline;

void insertToFile (const string&, Person*, Item*);

void updateInFile (const string&, Person*, Item*);

void removeFromFile (const string&, Person*, int);

#endif