#pragma once
#include <exception>

class InvalidPositionException : public std::exception
{
    virtual const char *what() const throw() { return "Invalid position"; }
} invalidPositionException;