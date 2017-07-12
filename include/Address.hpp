#ifndef _ADDRESS_HPP_
#define _ADDRESS_HPP_
#include "iostream"
#include "ParsingException.hpp"
#include "Proposals.hpp"
#include "Utils.hpp"
class Proposals;

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
    static std::vector<Address> search(Proposals *proposals);
private:
    std::string city;
    int streetNumber;
    std::string streetName;
    StreetType streetType;

    std::string baseCity;
    std::string baseStreetName;

    std::string streetTypeStr;

public:
    std::string getCity() { return this->city; }
    int getStreetNumber() { return this->streetNumber; }
    std::string getStreetName() { return this->streetName; }
    StreetType getStreetType() { return this->streetType; }
    std::string getStreetTypeStr() { return this->streetTypeStr; }

    std::string getBaseCity() { return this->baseCity; }
    std::string getBaseStreetName() { return this->baseStreetName; }
};

std::ostream &operator<<(std::ostream &os, Address &m);

#endif