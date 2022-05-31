#pragma once
#include "CSVManager/RowType.h"
#include <array>

class Player : public RowType
{
public:
  const static std::array<std::string, 4> correctFieldNames;

  std::vector<std::string> toStrings();
  void loadStrings(const std::vector<std::string> &rowValues);

  unsigned int id;
  std::string name;
  std::string password;
  unsigned int cash; // cash could be separate class

  bool operator==(Player const &p) const noexcept;
};
