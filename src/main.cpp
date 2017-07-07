#include "AutoCompletion.hpp"
#include "Address.hpp"

void print_usage()
{
    std::cout << ("USAGE\n\t./autoCompletion dictionnary\nDESCRIPTION\n\tdictionnary file, containing one address per line, serving as knowledge base\n");
}

void print_propositions(std::vector<Address> addresses)
{
    for (auto &address : addresses) 
    {

    }
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
                std::string query = "";
                std::string line;
                while (std::getline(std::cin, query))
                {
                    if (line == "ABORT")
                        return (84);
                    query += line[0];
                    std::cout << "Query: " << query;
                    if (addresses.size() > 1)
                        print_propositions(Address::search(query, addresses));
                }
            } catch (ParsingException *p) {

            }
        }
    }
}