#ifndef _PROPOSALS_HPP_
#define _PROPOSALS_HPP_
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>
#include <functional>
#include "Address.hpp"
class Address;
typedef std::function<bool(std::pair<char, int>, std::pair<char, int>)> Comparator;

enum ProposalState { 
    FirstChoice,
    CityChoice,
    CityNumberChoice,
    StreetChoice,
    StreetNumberChoice,
    AddressChoice
};

class Proposals {
public:
    Proposals(std::vector<Address> addresses);
    ~Proposals();
    
    bool apply(char character);
    void print();

    std::set<std::pair<char, int>, Comparator> computePossibility(std::vector<Address> addresses);
private:
    std::vector<Address> addresses;
    std::vector<Address> last_result;
    std::string query;
    std::vector<char> choices;
    ProposalState state;
    std::string selectedCity;
    std::string selectedStreet;

public:
    std::string getSelectedCity() { return this->selectedCity; }
    std::string getSelectedStreet() { return this->selectedStreet; }
    ProposalState getState() { return this->state; }
    std::vector<Address> getAddresses() { return this->addresses; }
    void chooseCity(std::string city);
    void chooseStreet(std::string street); 
    std::string getQuery() { return this->query; }
};

#endif