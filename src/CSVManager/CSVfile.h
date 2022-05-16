#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// CSV format:
// first row contains names of columns, separeted by separator
// records in rows
// values of records separated by separator

template <class RowType>
class CSVfile
{
private:
    std::string path;
    //    char separator = ','; // TODO: why seperator here if not used in this class
    std::vector<std::string> fieldNames;
    std::vector<RowType> rows;

public:
    CSVfile(std::string Path)
    {
        this->path = path;
        this->load();
    }
    void load()
    {
        fieldNames.clear();
        rows.clear();

        std::fstream file;
        file.open(path, std::ios::in);
        if (file.is_open())
        {
            std::string line;
            RowType firstRow;
            if (std::getline(file, line))
            {
                firstRow.load(line);
                fieldNames = firstRow.toStrings();
            }
            else
                return;
            while (std::getline(file, line))
            {
                RowType newRow;
                newRow.load(line);
                rows.push_back(newRow);
            }
        }
        else
        {
            // could not open file exception here
        }
    }
    void save();
    RowType &getRow(int rowN)
    {
        if (rows.size() >= rowN && rowN > 0)
        {
            return rows[rowN - 1];
        }
        else
        {
            // invalid rowN argument, row does not exist error
        }
    }
    RowType operator[](int rowN)
    {
        return getRow(rowN);
    }
};

class RowType
{
private:
    std::string content;
    const static std::vector<std::string> fieldNames;
    // char separator = ',';

public:
    static void validateFN();
    RowType();
    void load(std::string content); // needs to remove old content
    std::vector<std::string> toStrings()
    {
        std::vector<std::string> rowData;
        rowData.clear();
        if (content == "")
            return rowData;
        std::stringstream streamRow(content);
        std::string singleData;
        while (std::getline(streamRow, singleData, separator))
        {
            rowData.push_back(singleData);
        }
        return rowData;
    }
    // RowType fromStrings();
};
