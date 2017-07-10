#ifndef _ADDRESS_HPP_
#define _ADDRESS_HPP_
#include "iostream"
#include "ParsingException.hpp"

#include "Utils.hpp"

enum StreetType { 
    Allee,
    Avenue,
    Boulevard,
    Chemin,
    Impasse,
    Place,
    Quai,
    Rue,
    Square 
};

class Address {
public:
    Address(int streetNumber, std::string city, std::string streetName, std::string streetType);
    ~Address();
    static std::vector<Address> parse(std::string file);
    static std::vector<Address> search(std::string *query, std::string *target_city, std::string *target_street, std::vector<Address> addresses);
private:
    std::string city;
    int streetNumber;
    std::string streetName;
    StreetType streetType;

public:
    std::string getCity() { return this->city; }
    int getStreetNumber() { return this->streetNumber; }
    std::string getStreetName() { return this->streetName; }
    StreetType getStreetType() { return this->streetType; }
};

std::ostream &operator<<(std::ostream &os, Address &m);

#endif