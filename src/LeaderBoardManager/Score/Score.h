#pragma once
#include "../../CSVManager/RowType.h"
#include <array>

class Score : public RowType
{
public:
  const static std::array<std::string, 3> correctFieldNames;

  Score(int a = 0)
  {
    score = 0;
    playerId = 0;
    gameId = 0;
  }

  std::vector<std::string> toStrings();
  void loadStrings(const std::vector<std::string> &rowValues);

  unsigned int playerId;
  unsigned int gameId;
  unsigned int score;

  unsigned int getScore() const noexcept
  {
    return score;
  }

  unsigned int getGameId() const noexcept
  {
    return gameId;
  }

  bool operator>(Score const &s) const noexcept
  {
    return score > s.score;
  }
  bool operator<(Score const &s) const noexcept
  {
    return score < s.score;
  }

  friend std::ostream &operator<<(std::ostream &os, Score &s)
  {
    os << s.playerId << ',' << s.gameId << ',' << s.score;
    return os;
  }
};
