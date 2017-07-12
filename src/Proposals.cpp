#include "Proposals.hpp"

Proposals::Proposals(std::vector<Address> addresses)
{
    this->addresses = addresses;
    this->state = FirstChoice;
}
Proposals::~Proposals() 
{
    
}
    
bool Proposals::apply(char character)
{
    if(std::find(choices.begin(), choices.end(), character) == choices.end())
        return false;

    if (this->state == CityNumberChoice)
    {
        int index = character - 48;
        this->chooseCity(last_result.at(index - 1).getCity());
    }
    else if (this->state == StreetNumberChoice)
    {
        int index = character - 48;
        this->chooseStreet(last_result.at(index - 1).getStreetName());
    }
    else if (this->state == AddressChoice)
    {
        int index = character - 48;
        std::cout << "=> " << last_result.at(index - 1) << "\n";
        exit(0);
    }
    else
        query += std::tolower(character);
    last_result = Address::search(this);
    if (last_result.size() == 1)
    {
        std::cout << "=> " << last_result.at(0) << "\n";
        exit(0);
    }
    return true;
}

void Proposals::print()
{
    int index = 0;
    if (this->state == FirstChoice) // first printing
    {
        this->state = CityChoice;
        std::set<std::pair<char, int>, Comparator> possibility = computePossibility(addresses);
        choices = std::vector<char>();
        for (std::pair<char, int> element : possibility)
            choices.push_back((char) std::tolower(element.first));
        for (std::pair<char, int> element : possibility)
        {
            if (index != 0)
                std::cout << " ";
            if (index == 5)
                break;
            std::cout << "{" << (char) std::tolower(element.first) << "}";
            index++;
        }
        std::cout << std::endl;
    }
    else if (this->state == CityChoice) 
    {
        std::set<std::pair<char, int>, Comparator> possibility = computePossibility(last_result);
        choices = std::vector<char>();
        if (this->state == CityNumberChoice)
        {
           this->print();
           return;
        }
        for (std::pair<char, int> element : possibility)
            choices.push_back((char) std::tolower(element.first));
        if (possibility.size() == 1)
        {
            this->apply((*possibility.begin()).first);
            this->print();
            return;
        }
        for (std::pair<char, int> element : possibility)
        {
            if (index != 0)
                std::cout << " ";
            if (index == 5)
                break;
            std::cout << "{" << toUpper(query) << (char) std::tolower(element.first) << "}";

            index++;
        }
        std::cout << std::endl;
    }
    else if (this->state == CityNumberChoice) 
    {
        choices = std::vector<char>();
        for (auto &address : last_result) 
        {
            if (index != 0)
                std::cout << " ";
            std::string substr = address.getCity();
            std::cout << "{ " << (index + 1) << " : " << address.getCity() << " }";
            choices.push_back((char) (index + 49));
            index++;
        }
        std::cout << std::endl;
    }
    else if (this->state == StreetChoice) 
    {
        std::set<std::pair<char, int>, Comparator> possibility = computePossibility(last_result);
        choices = std::vector<char>();
        if (this->state == StreetNumberChoice)
        {
           this->print();
           return;
        }
        for (std::pair<char, int> element : possibility)
            choices.push_back((char) std::tolower(element.first));
        if (possibility.size() == 1)
        {
            this->apply((*possibility.begin()).first);
            this->print();
            return;
        }
        for (std::pair<char, int> element : possibility)
        {
            if (index != 0)
                std::cout << " ";
            if (index == 5)
                break;
            std::cout << "{" << toUpper(selectedCity) << ", " << toUpper(query) << (char) std::tolower(element.first) << "}";
            index++;
        }
        std::cout << std::endl;
    }
    else if (this->state == StreetNumberChoice) 
    {
        choices = std::vector<char>();
        for (auto &address : last_result) 
        {
            if (index != 0)
                std::cout << " ";
            std::string substr = address.getCity();
            std::cout << "{ " << (index + 1) << " : " << toUpper(address.getCity()) << ", " << address.getStreetNumber() << " " << address.getStreetTypeStr() << " " << toUpper(address.getStreetName()) << " }";
            choices.push_back((char) (index + 49));
            index++;
        }
        std::cout << std::endl;
    }
    else if (this->state == AddressChoice) 
    {
        std::set<std::pair<char, int>, Comparator> possibility = computePossibility(last_result);
        choices = std::vector<char>();
        for (auto &address : last_result) 
        {
            if (index != 0)
                std::cout << " ";
            std::string substr = address.getCity();
            std::cout << "{ " << (index + 1) << " : " << toUpper(address.getCity()) << ", " << address.getStreetNumber() << " " << address.getStreetTypeStr() << " " << toUpper(address.getStreetName()) << " }";
            choices.push_back((char) (index + 49));
            index++;
        }
        std::cout << std::endl;
    }

}

std::set<std::pair<char, int>, Comparator> Proposals::computePossibility(std::vector<Address> addresses)
{
    std::map<char, int> values;
    for (auto &address : addresses) 
    {
        std::string buffer;
        std::stringstream stream;
        if (state == CityChoice)
            stream = std::stringstream(address.getCity());
        else if (state == StreetChoice)
            stream = std::stringstream(address.getStreetName());
        while (stream >> buffer)
        {
            transform(buffer.begin(), buffer.end(), buffer.begin(),(int (*)(int))tolower);
            if (this->query == "")
                values[buffer.at(0)]++;
            else if (buffer.find(this->query) != std::string::npos)
            {
                char caracter_key;
                if (buffer.size() == (this->query).size() + buffer.find(this->query))
                {
                    if (state == CityChoice)
                        this->state = CityNumberChoice;
                    else if (state == StreetChoice)
                        this->state = StreetNumberChoice;
                    return std::set<std::pair<char, int>, Comparator>();
                }
                else
                {
                    caracter_key = buffer.at((this->query).size() + buffer.find(this->query));
               }
               values[caracter_key]++;
            }
        }
    }

    Comparator compFunctor = [](std::pair<char, int> elem1, std::pair<char, int> elem2)
                                {
                                    if (elem1.second == elem2.second)
                                        return elem1.first < elem2.first;
                                    return elem1.second > elem2.second;
                                };
 
    std::set<std::pair<char, int>, Comparator> valuesSet(values.begin(), values.end(), compFunctor);
    return valuesSet;
}

void Proposals::chooseCity(std::string city)
{
    this->query = "";
    this->state = StreetChoice; 
    this->selectedCity = city; 
}

void Proposals::chooseStreet(std::string street)
{
    this->query = ""; 
    this->state = AddressChoice; 
    this->selectedStreet = street; 
}