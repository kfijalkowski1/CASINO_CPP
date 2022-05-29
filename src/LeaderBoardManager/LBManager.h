#include <iostream>
#include <fstream>
#include "src/CSVManager/CSVfile.h"
#include "src/LeaderBoardManager/Score/Score.h"
/*
egzample line in CSV file:
player id, game id, score
*/
// update LB
// save temp
//
class LBReader : public CSVfile<Score>
{
private:
public:
    void pushScore(Score const &s)
    {
        rows.push_back(s);
    }

    void saveScores();

    std::vector<Score> getLeaders(unsigned int gameId);
};