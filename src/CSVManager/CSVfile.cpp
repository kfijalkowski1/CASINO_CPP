#include "CSVfile.h"

template <typename RowType>
CSVfile<RowType>::CSVfile()
{
}
template <typename RowType>
CSVfile<RowType>::CSVfile(std::string path)
{
    this->path = path;
    this->load(path);
}
template <typename RowType>
bool CSVfile<RowType>::load(std::string path)
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
            return false;
        while (std::getline(file, line))
        {
            RowType newRow;
            newRow.load(line);
            rows.push_back(newRow);
        }
        return true;
    }
    return false;
}
template <typename RowType>
RowType CSVfile<RowType>::getRow(int rowN)
{
    if (rows.end() - rows.begin() >= rowN && rowN > 0)
    {
        return rows[rowN - 1];
    }
    else
    {
        RowType empty;
        return empty;
    }
}

RowType::RowType()
{
    content = "";
}
void RowType::load(std::string content)
{
    this->content = content;
}
std::vector<std::string> RowType::toStrings()
{
    std::vector<std::string> rowData;
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
/*
std::fstream file;
    file.open(path, std::ios::in);
    std::string line, header, word;
    std::getline(file, line);
    std::stringstream str(line);
    int counter = 0;
    while (std::getline(str, header, splitting_char))
    {
        if (header == ColumnName)
            break;
        else
            counter++;
    }
    for (rowN; rowN >= 0; rowN--)
    {
        std::getline(file, line);
    }
    std::stringstream str2(line);
    for (counter; std::getline(str2, word, splitting_char) && counter > 0; counter--)
    {
    }
    return word;
*/