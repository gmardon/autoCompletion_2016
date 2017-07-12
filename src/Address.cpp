#include "Address.hpp"

Address::Address(int streetNumber, std::string city, std::string streetName, std::string streetType)
{
    this->streetNumber = streetNumber;
    this->baseCity = city;
    this->baseStreetName = streetName;

    city.erase(std::remove(city.begin(), city.end(), '\''), city.end());
    this->city = toLower(city);
    streetName.erase(std::remove(streetName.begin(), streetName.end(), '\''), streetName.end());
    this->streetName = toLower(streetName);

    if (streetType == "allée")
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

    this->streetTypeStr = streetType;
}

Address::~Address()
{

}

std::vector<Address> Address::parse(std::string file)
{
    std::vector<Address> addresses;
    std::ifstream input(file);
    std::regex address_regex("^([\\w\\s]*), ([\\d]+) (impasse|quai|rue|square|allée|place|boulevard|rue|chemin|avenue) ([\\w\\s-zàâçéèêëîïôûùüÿñæœ']+)$");
    std::regex case1_regex("^([\\w\\s]*) ([\\d]+) (impasse|quai|rue|square|allée|place|boulevard|rue|chemin|avenue) ([\\w\\s-zàâçéèêëîïôûùüÿñæœ']+)$");
    std::regex case2_regex("^([\\d]+) (impasse|quai|rue|square|allée|place|boulevard|rue|chemin|avenue) ([\\w\\s-zàâçéèêëîïôûùüÿñæœ']+), ([\\w\\s]*)$");
    std::smatch matches;
    for( std::string line; getline( input, line );)
    {
        if (regex_search(line, matches, address_regex))
        {
            Address *address = new Address(atoi(matches[2].str().c_str()), matches[1].str(), matches[4].str(), matches[3].str());
            addresses.push_back(*address);
        }
        else if (regex_search(line, matches, case1_regex))
        {
            Address *address = new Address(atoi(matches[2].str().c_str()), matches[1].str(), matches[4].str(), matches[3].str());
            addresses.push_back(*address);     
        }
        else if (regex_search(line, matches, case2_regex))
        {
            Address *address = new Address(atoi(matches[1].str().c_str()), matches[4].str(), matches[3].str(), matches[2].str());
            addresses.push_back(*address);     
        }
        else
        {
            std::cout << "Unknown address.\n";
            exit(84);
        }
    }
    return (addresses);
}

std::vector<Address> Address::search(Proposals *proposals)
{
    std::vector<Address> matching;
    if (proposals->getState() == CityChoice)
    {
        std::vector<std::string> cities;
        for (auto &address : proposals->getAddresses()) 
        {
            std::string buffer;
            std::stringstream stream(address.getCity());
            while (stream >> buffer)
            {
                transform(buffer.begin(), buffer.end(), buffer.begin(),(int (*)(int))tolower);
                if (stringncasecmp(buffer, proposals->getQuery(), proposals->getQuery().length()))
                {                                
                    matching.push_back(address);
                    if(std::find(cities.begin(), cities.end(), address.getCity()) == cities.end())
                    {
                        cities.push_back(address.getCity());
                    }
                    break;
                }
            }
        }
        if (cities.size() == 1)
        {
            proposals->chooseCity(cities.at(0));
            return Address::search(proposals);
        }
    }
    else if (proposals->getState() == StreetChoice)
    {
        std::vector<std::string> streets;
        for (auto &address : proposals->getAddresses()) 
        {
            if (equals_ignore_case(address.getCity(), proposals->getSelectedCity()))
            {
                std::string buffer;
                std::stringstream stream(address.getStreetName());
                while (stream >> buffer)
                {
                    if (stringncasecmp(buffer, proposals->getQuery(), (proposals->getQuery()).length()) || proposals->getQuery() == "")
                    {
                        matching.push_back(address);
                        if(std::find(streets.begin(), streets.end(), address.getStreetName()) == streets.end())
                        {
                            streets.push_back(address.getStreetName());
                        }
                        break;
                    }
                }   
            }
        }
        if (streets.size() == 1)
        {
            proposals->chooseStreet(streets.at(0));
            return Address::search(proposals);
        }
    }
    else if (proposals->getState() == AddressChoice)
    {
        std::vector<std::string> streets;
        for (auto &address : proposals->getAddresses()) 
        {
            if (equals_ignore_case(address.getCity(), proposals->getSelectedCity()))
            {
                if (equals_ignore_case(address.getStreetName(), proposals->getSelectedStreet()))
                {
                    matching.push_back(address);
                }
            }
        }
    }
    return (matching);
}

std::ostream &operator<<(std::ostream &os, Address &addr)
{
    return os << addr.getBaseCity() << ", " << addr.getStreetNumber() << " " << addr.getStreetTypeStr() << " " << addr.getBaseStreetName();
}