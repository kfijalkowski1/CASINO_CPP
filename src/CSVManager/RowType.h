#pragma once

#include <string>
#include <vector>

class RowType
{
  public:
    virtual std::vector<std::string> toStrings() = 0;
    virtual void loadStrings(const std::vector<std::string> &rowValues) = 0;
};
