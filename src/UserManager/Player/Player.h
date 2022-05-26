#pragma once
#include "CSVManager/RowType.h"

class Player : public RowType
{
  public:
    const static std::vector<std::string> correctFieldNames;

    Player();

    std::vector<std::string> toStrings();
    void loadStrings(const std::vector<std::string> &rowValues);

    unsigned int id;
    std::string name;
    std::string password;
    unsigned int cash;
};
