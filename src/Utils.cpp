#include "Utils.hpp"

bool equals_ignore_case(const std::string& a, const std::string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

bool stringncmp(const std::string& a, const std::string& b, size_t len)
{
    return strncmp(a.c_str(), b.c_str(), len) == 0;
}

bool stringncasecmp(const std::string& a, const std::string& b, size_t len)
{
    return strncasecmp(a.c_str(), b.c_str(), len) == 0;
}


std::string toUpper(std::string str)
{
    std::string newstr(str);
    std::transform(newstr.begin(), newstr.end(),newstr.begin(), ::toupper);
    return newstr;
}

std::string toUpperQuery(std::string str, std::string query)
{
    std::string newstr(str);
    int firstIndex = 0;
    int lastIndex = 0;
    firstIndex = newstr.find(query);
    lastIndex = newstr.find(" ", firstIndex);
    if (lastIndex == 0)
        lastIndex = newstr.size();
    newstr.replace(firstIndex, query.size() + firstIndex + 1, toUpper(str.substr(firstIndex, lastIndex)));
    return newstr;
}

std::string toLower(std::string str)
{
    std::string newstr(str);
    std::transform(newstr.begin(), newstr.end(), newstr.begin(), ::tolower);
    return newstr;
}