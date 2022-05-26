#include <exception>

class OutOfBoundsException : public std::exception
{
    virtual const char *what() const throw()
    {
        return "Array access out of bounds";
    }
} outOfBoundsException;

class FileNotFoundException : public std::exception
{
    virtual const char *what() const throw() { return "File not found"; }
} fileNotFoundException;

class IncorrectFieldNamesException : public std::exception
{
    virtual const char *what() const throw() { return "Incorrect field names"; }
} incorrectFieldNamesException;