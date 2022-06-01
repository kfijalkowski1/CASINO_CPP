#pragma once
#include "CSVManager/CSVfile.h"
#include "LeaderBoardManager/Score/Score.h"
#include <fstream>
#include <iostream>
/*
egzample line in CSV file:
player id, game id, score
*/
// update LB
// save temp
//
class LBReader
{
private:
  CSVfile<Score> file;

public:
  LBReader();

  void pushBack(Score &s);
  // delete not done, donno if needed
  // void deleteScore(Score const &s) noexcept;

  std::vector<Score> getLeaders(unsigned int gameId);
};