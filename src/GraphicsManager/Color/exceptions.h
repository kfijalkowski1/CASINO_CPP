#pragma once
#include <exception>

class InvalidColorException : public std::exception
{
    virtual const char *what() const throw() { return "Invalid color"; }
} invalidColorException;