#pragma once
#include "CSVManager/RowType.h"

class Score : public RowType
{
public:
  const static std::vector<std::string> correctFieldNames;

  // Score();  //imo not ness to have empty constr

  std::vector<std::string> toStrings();
  void loadStrings(const std::vector<std::string> &rowValues);

  unsigned int playerId;
  unsigned int gameId;
  unsigned int score;
};
