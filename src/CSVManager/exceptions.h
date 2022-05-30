#pragma once
#include <exception>

class OutOfBoundsException : public std::exception
{
    virtual const char *what() const throw()
    {
        return "Array access out of bounds";
    }
};

class FileNotFoundException : public std::exception
{
    virtual const char *what() const throw() { return "File not found"; }
};

class IncorrectFieldNamesException : public std::exception
{
    virtual const char *what() const throw() { return "Incorrect field names"; }
};
