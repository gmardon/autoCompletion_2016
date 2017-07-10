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
    std::transform(str.begin(), str.end(),str.begin(), ::toupper);
    return str;
}

std::string toLower(std::string str)
{
    std::transform(str.begin(), str.end(),str.begin(), ::toupper);
    return str;
}