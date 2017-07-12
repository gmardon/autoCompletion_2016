#include "Address.hpp"
#include "UnknownAddressException.hpp"

Address::Address(int streetNumber, std::string city, std::string streetName, std::string streetType)
{
    this->streetNumber = streetNumber;
    this->city = city;
    this->streetName = streetName;

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
}

std::string streetTypeToString(StreetType streetType)
{
    if (streetType == Allee)
        return ("allée");
    else if (streetType == Avenue)
        return ("avenue");
    else if (streetType == Boulevard)
        return ("boulevard");
    else if (streetType == Chemin)
        return ("chemin");
    else if (streetType == Impasse)
        return ("impasse");
    else if (streetType == Place)
        return ("place");
    else if (streetType == Quai)
        return ("quai");
    else if (streetType == Rue)
        return ("rue");
    else if (streetType == Quai)
        return ("quai");
    return ("");
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

std::vector<Address> Address::search(std::string *query, std::string *target_city, std::string *target_street, std::vector<Address> addresses, std::vector<Address> last_result)
{
    std::vector<Address> matching;
    transform((*query).begin(), (*query).end(), (*query).begin(),(int (*)(int))tolower);
    if (*target_city == "")
    {
        std::vector<std::string> cities;
        for (auto &address : addresses) 
        {
            std::string city = address.getCity();
            std::string buffer;
            std::stringstream stream(city);
            while (stream >> buffer)
            {
                transform(buffer.begin(), buffer.end(), buffer.begin(),(int (*)(int))tolower);
                if (stringncasecmp(buffer, *query, (*query).length()))
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
            *target_city = cities.at(0);
            transform((*target_city).begin(), (*target_city).end(), (*target_city).begin(),(int (*)(int))toupper);
            *query = "";
        }
    }
    else if (*target_street == "")
    {
        std::vector<std::string> streets;
        for (auto &address : addresses) 
        {
            if (equals_ignore_case(address.getCity(), *target_city))
            {
                if (stringncasecmp(address.getStreetName(), *query, (*query).length()))
                {
                    matching.push_back(address);
                    if(std::find(streets.begin(), streets.end(), toUpper(address.getStreetName())) == streets.end())
                    {
                        streets.push_back(toUpper(address.getStreetName()));
                    }
                }
            }
        }
        if (streets.size() == 1)
        {
            *target_street = streets.at(0);
            transform((*target_street).begin(), (*target_street).end(), (*target_street).begin(),(int (*)(int))toupper);
            *query = "";
        }
    }
    else
    {
        std::vector<Address> sub;
        sub.push_back(last_result.at(std::stoi(*query) - 1));
        return (sub);
    }
    return (matching);
}

std::ostream &operator<<(std::ostream &os, Address &addr)
{
    return os << addr.getCity() << ", " << addr.getStreetNumber() << " " << streetTypeToString(addr.getStreetType()) << " " << addr.getStreetName();
}