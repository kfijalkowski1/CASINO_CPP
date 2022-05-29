#pragma once
#include <iostream>
#include <fstream>
#include "/home/gambolkf/projekty/PROI/proi-project-casino.o-sl-aj-kf/src/CSVManager/CSVfile.h"
#include "/home/gambolkf/projekty/PROI/proi-project-casino.o-sl-aj-kf/src/LeaderBoardManager/Score/Score.h"
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
    void pushScore(Score const &s)
    {
        (*filePtr).push_back(s);
    }
    // delete not done, donno if needed
    // void deleteScore(Score const &s) noexcept;

    void saveScores();

    std::vector<Score> getLeaders(unsigned int gameId);
};