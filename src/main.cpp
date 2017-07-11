#include "Utils.hpp"
#include "Address.hpp"

void print_usage()
{
    std::cout << ("USAGE\n\t./autoCompletion dictionnary\nDESCRIPTION\n\tdictionnary file, containing one address per line, serving as knowledge base\n");
}

void list_propositions(std::string *query, std::string *target_city, std::string *target_street, std::vector<Address> addresses)
{
    if (*target_street != "")
    {
        int index = 1;
        for (auto &address : addresses) 
        {
            std::string addr_s;
            std::ostringstream os;
            os << address;
            addr_s = toUpper(os.str());
            std::cout << "{ " << index << " : " << addr_s << " } ";
            index++;
        }
        std::cout << std::endl;
        return;
    }
    std::map<char, int> values;
    for (auto &address : addresses) 
    {
        std::string buffer;
        std::stringstream stream;
        if (*target_city == "")
            stream = std::stringstream(address.getCity());
        else
            stream = std::stringstream(address.getStreetName());
        while (stream >> buffer)
        {
            transform(buffer.begin(), buffer.end(), buffer.begin(),(int (*)(int))tolower);
            if (*query == "")
                values[std::tolower(buffer.at(0))]++;
            else if (buffer.find(*query) != std::string::npos)
            {
                char caracter_key;
                if (buffer.size() <= (*query).size() + buffer.find(*query))
                {
                    if (*target_city == "")
                        caracter_key = address.getCity().at((*query).size() + buffer.find(*query));
                    else
                    {
                        caracter_key = address.getStreetName().at((*query).size() + buffer.find(*query));
                    }
                }
                else
                {
                    caracter_key = buffer.at((*query).size() + buffer.find(*query));
               }
                values[std::tolower(caracter_key)]++;
            }
        }
    }
    typedef std::function<bool(std::pair<char, int>, std::pair<char, int>)> Comparator;
    Comparator compFunctor = [](std::pair<char, int> elem1, std::pair<char, int> elem2)
                                {
                                    if (elem1.second == elem2.second)
                                        return elem1.first < elem2.first;
                                    return elem1.second > elem2.second;
                                };
 
    std::set<std::pair<char, int>, Comparator> valuesSet(values.begin(), values.end(), compFunctor);
    int index = 0;
    if (valuesSet.size() == 1)
    {
        *query += valuesSet.begin()->first;
        std::vector<Address> result = Address::search(query, target_city, target_street, addresses, std::vector<Address>());
        if (result.size() == 1)
        {
            std::cout << "=> " << result.at(0) << "\n";
        }
        else
            list_propositions(query, target_city, target_street, result);
        return;
    }
    for (std::pair<char, int> element : valuesSet)
    {
        if (index == 5)
            break;
        if (*target_city != "")
            std::cout << "{" << *target_city << ", " << toUpper(*query) << element.first << "} ";
        else 
            std::cout << "{" << toUpper(*query) << element.first << "} ";
        index++;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        print_usage();
        return (84);
    }
    else
    {
        if (strcmp(argv[1], "-h") == 0)
        {
            print_usage();
            return (84);
        }
        else
        {   
            try {
                std::vector<Address> addresses = Address::parse(argv[1]);
                std::vector<Address> last_result;
                std::vector<Address> result;
                std::string query = "";
                std::string city = "";
                std::string street = "";
                std::string line;
                list_propositions(&query, &city, &street, addresses);              
                while (std::getline(std::cin, line))
                {
                    if (line == "ABORT")
                        return (84);
                    query += std::tolower(line[0]);
                    last_result = result;
                    result = Address::search(&query, &city, &street, addresses, last_result);
                    if (result.size() == 1)
                    {
                        std::cout << "=> " << result.at(0) << "\n";
                        return (0);
                    }
                    else
                        list_propositions(&query, &city, &street, result);
                }
            } catch (ParsingException *p) {

            }
        }
    }
}