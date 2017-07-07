#include "Address.hpp"

Address::Address(int streetNumber, std::string city, std::string streetName, std::string streetType)
{
    std::cout << "Address ('" << streetNumber << "', '" << city << "', '" << streetName << "', '" << streetType << "')\n";
    this->streetNumber = streetNumber;
    this->city = city;
    this->streetName = streetName;

    if (streetType == "allee")
        this->streetType = Allee;
    else if (streetType == "avenue")
        this->streetType = Avenue;
    else if (streetType == "boulevard")
        this->streetType = Boulevard;
    else if (streetType == "chemin")
        this->streetType = Chemin;
    else if (streetType == "impasse")
        this->streetType = Impasse;
    else if (streetType == "place")
        this->streetType = Place;
    else if (streetType == "quai")
        this->streetType = Quai;
    else if (streetType == "rue")
        this->streetType = Rue;
    else if (streetType == "quai")
        this->streetType = Square;
}

Address::~Address()
{

}

std::vector<Address> Address::parse(std::string file)
{
    std::vector<Address> addresses;
    std::ifstream input(file);
    std::regex address_regex("^([\\w\\s]*), ([\\d]+) (impasse|quai|rue|square|allée|place|boulevard|rue|chemin|avenue) ([\\w\\s-zàâçéèêëîïôûùüÿñæœ']+)$");
    std::smatch matches;
    for( std::string line; getline( input, line );)
    {
        if (regex_search(line, matches, address_regex))
        {
            Address *address = new Address(atoi(matches[2].str().c_str()), matches[1].str(), matches[4].str(), matches[3].str());
        }
        else
        {
            // cannot parse
        }
    }
    return (addresses);
}

std::vector<Address> Address::search(std::string query, std::vector<Address> addresses)
{
    std::vector<Address> matching;
    for (auto &address : addresses) 
    {
        //if (address->)
    }
    return (matching);
}