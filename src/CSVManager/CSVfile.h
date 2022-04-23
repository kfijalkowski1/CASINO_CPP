#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// CSV format:
// first row contains names of columns, separeted by separator
// records in rows
// values of records separated by separator

template <typename RowType>
class CSVfile
{
private:
    std::string path; // "../data/players.txt"
    char separator = ',';
    std::vector<std::string> fieldNames;
    std::vector<RowType> rows;

public:
    CSVfile();
    CSVfile(std::string Path);

    bool load(std::string path); // returns true if succesfull
    // bool save();                 // returns false if exception occured
    RowType getRow(int rowN);
    // std::string readCell(int rowN, std::string columnName);
};

class RowType
{
private:
    std::string content;
    char separator = ',';

public:
    RowType();
    void load(std::string content); // needs to remove old content
    std::vector<std::string> toStrings();
    // RowType fromStrings();
};