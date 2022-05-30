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
    CSVfile<Score> *filePtr;

  public:
    LBReader()
    {
        std::string path = "data/LBoardExample.csv";
        CSVfile<Score> file(path);
        filePtr = &file;
    }
    void pushScore(Score const &s) { (*filePtr).push_back(s); }
    // delete not done, donno if needed
    // void deleteScore(Score const &s) noexcept;

    void saveScores();

    std::vector<Score> getLeaders(unsigned int gameId);
};