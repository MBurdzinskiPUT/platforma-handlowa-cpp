#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <vector>
#include <string>

using namespace std;

template <typename T>
bool removeByValue (const T item, vector<T>& vector) {

    for (auto it = vector.begin(); it < vector.end(); it++) {
        if ((*it) == item) {
            vector.erase(it);
            return true;
        }
    }
    return false;
}

template <typename T>
T findByName (const string& name, const vector<T>& vector) {

    for (auto it = vector.cbegin(); it < vector.cend(); it++) {
        if ((*it)->getName() == name) {
            return *it;
        }
    }
    throw "Error: Object with this name could not be found";
}

template <typename T>
T findById (const int id, const vector<T>& vector) {

    for (auto it = vector.cbegin(); it < vector.cend(); it++) {
        if ((*it)->getId() == id) {
            return *it;
        }
    }
    throw "Error: Object with this id could not be found";
}

#endif