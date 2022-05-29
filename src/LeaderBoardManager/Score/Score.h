#pragma once
#include "../../CSVManager/RowType.h"
#include <array>

class Score : public RowType
{
public:
  const static std::array<std::string, 3> correctFieldNames;

  std::vector<std::string> toStrings();
  void loadStrings(const std::vector<std::string> &rowValues);

  unsigned int playerId;
  unsigned int gameId;
  unsigned int score;

  bool operator>(Score const &s) const noexcept
  {
    return score > s.score;
  }
  bool operator<(Score const &s) const noexcept
  {
    return score < s.score;
  }
};
