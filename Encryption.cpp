#include "Encryption.hpp"

string encrypt (string str) {

    string temp;
    for (int i = 0; i < str.size(); i++) {
        temp += (str[i] ^ 0x51) + 50;
    }
    return temp;
}

string decrypt (string str) {

    string temp;
    for (int i = 0; i < str.size(); i++) {
        temp += (str[i] - 50) ^ 0x51;
    }
    return temp;
}

size_t rshash (string str) {

    size_t prime[2] = {378551, 63689};
    size_t hash = 0;
    size_t mask = 0x7FFFFFFFFFFFFFFF;
    for (int i = 0; i < str.length(); i++) {
        hash *= prime[1];
        hash += str[i];
        prime[1] *= prime[0];
    }
    return hash & mask;
}