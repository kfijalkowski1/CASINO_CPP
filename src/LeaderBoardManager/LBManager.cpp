#include "LBManager.h"

void LBReader::saveScores()
{
    std::ofstream myfile;
    myfile.open("data/LBoardExample.csv");
    for (auto i : (*filePtr))
    {
        myfile << i;
    }
    myfile.close();
}

std::vector<Score> LBReader::getLeaders(unsigned int gameId)
{
    // returns vector of 3 best scores, best at [0]
    std::vector<Score> result;
    Score bestScore;
    Score secondScore;
    Score thirdScore;
    for (auto i : (*filePtr)) // find biggest scores
    {
        if (i.getGameId() == gameId)
        {
            if (i.getScore() > bestScore.getScore())
            {
                bestScore = i;
            }
            else if (i.getScore() > secondScore.getScore())
            {
                secondScore = i;
            }
            else if (i.getScore() > thirdScore.getScore())
            {
                thirdScore = i;
            }
        }
    }
    result.push_back(bestScore);
    result.push_back(secondScore);
    result.push_back(thirdScore);
    return result;
}

// nie dokończone nie wiem czy potrzebne
// void LBReader::deleteScore(Score const &s) noexcept
// {
//     for (auto i : (*filePtr))
//     {
//         if (i == s)
//         {
//             delete *i;
//         }
//     }
// }