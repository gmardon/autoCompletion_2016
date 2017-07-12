#include "Utils.hpp"
#include "Address.hpp"
#include "Proposals.hpp"

void print_usage()
{
    std::cout << ("USAGE\n\t./autoCompletion dictionnary\nDESCRIPTION\n\tdictionnary file, containing one address per line, serving as knowledge base\n");
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
            return (0);
        }
        else
        {   
            try {
                std::vector<Address> addresses = Address::parse(argv[1]);
                Proposals proposals = Proposals(addresses);
                std::string line;
                proposals.print();    
                while (std::getline(std::cin, line))
                {
                    if (line == "ABORT")
                        return (84);
                    if (!proposals.apply(std::tolower(line[0])))
                    {
                        std::cout << "Unknown address.\n";
                        return (84);
                    }
                    proposals.print();
                }
            } catch (ParsingException *p) {

            }
        }
    }
}