#ifndef _ADDRESS_HPP_
#define _ADDRESS_HPP_
#include "iostream"
#include "ParsingException.hpp"
#include "fstream"
#include "regex"
#include "vector"

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
    static std::vector<Address> search(std::string query, std::vector<Address> addresses);
    std::string getCity();
    int getStreetNumber();
    std::string getStreetName();
    StreetType getStreetType();

private:
    std::string city;
    int streetNumber;
    std::string streetName;
    StreetType streetType;
};

#endif