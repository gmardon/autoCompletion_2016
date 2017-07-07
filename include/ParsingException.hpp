#ifndef _PARSING_EXCEPTION_HPP_
#define _PARSING_EXCEPTION_HPP_
#include <iostream>
class ParsingException : public std::exception
{
public:
    virtual const char* what() const throw () { return "Something bad happend."; }
};
#endif