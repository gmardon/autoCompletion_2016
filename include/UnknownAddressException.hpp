#ifndef _UNKNOWN_ADDRESS_EXCEPTION_HPP_
#define _UNKNOWN_ADDRESS_EXCEPTION_HPP_
#include <iostream>
class UnknownAddressException : public std::exception
{
public:
    virtual const char* what() const throw () { return "Unknown address."; }
};
#endif