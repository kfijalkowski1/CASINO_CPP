#pragma once

#include "RowType.h"
#include "exceptions.h"
#include <fstream>
#include <string>
#include <vector>

// CSV format:
// first row contains names of columns, separeted by separator
// records in rows
// values of records separated by separator

template <class Row>
class CSVfile
{
private:
    std::string path;
    std::string separator = ",";
    std::vector<std::string> fieldNames;
    std::vector<Row> rows;

public:
    CSVfile(std::string path, std::string separator)
        : path(path), separator(separator)
    {
        static_assert(std::is_base_of<RowType, Row>::value,
                      "Row must derive from RowType");

        this->load();
    }
    CSVfile(std::string path) : CSVfile(path, ",") {}

    std::vector<std::string> getLine(std::ifstream &file) const
    {
        std::vector<std::string> result;

        std::string line;
        if (std::getline(file, line))
        {
            size_t pos = 0;
            while ((pos = line.find(separator)) != std::string::npos)
            {
                result.push_back(line.substr(0, pos));
                line.erase(0, pos + separator.length());
            }
            result.push_back(line);
        }
        return result;
    }

    bool validateFieldNames(const std::vector<std::string> &fieldNames) const
    {
        if (Row::correctFieldNames.size() != fieldNames.size())
            return false;

        return std::equal(Row::correctFieldNames.begin(),
                          Row::correctFieldNames.end(), fieldNames.begin());
    }

    void load()
    {
        fieldNames.clear();
        rows.clear();

        std::ifstream file(path);
        if (!file.is_open())
            throw fileNotFoundException;

        fieldNames = getLine(file);
        if (!validateFieldNames(fieldNames))
            throw incorrectFieldNamesException;

        std::vector<std::string> rawRow;
        while ((rawRow = getLine(file)).size() > 0)
        {
            rows.push_back(Row());
            rows.back().loadStrings(rawRow);
        }

        file.close();
    }

    void save();

    Row &getRow(std::size_t rowN)
    {
        if (rows.size() > rowN && rowN >= 0)
            return rows[rowN];
        else
            throw outOfBoundsException;
    }
    Row &operator[](std::size_t rowN) { return getRow(rowN); }
    const Row &operator[](std::size_t rowN) const { return getRow(rowN); }

    auto begin() { return rows.begin(); }
    auto front() { return rows.front(); }
    auto end() { return rows.end(); }
    auto back() { return rows.back(); }
    auto size() { return rows.size(); }
    auto push_back(const Row &val) { return rows.push_back(val); }
    auto pop_back() { return rows.pop_back(); }
};
