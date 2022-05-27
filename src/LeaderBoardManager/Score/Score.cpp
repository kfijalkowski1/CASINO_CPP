#include "Score.h"

const std::array<std::string, 3> Score::correctFieldNames = {"playerId",
                                                             "gameId", "score"};

std::vector<std::string> Score::toStrings()
{
    std::vector<std::string> result;
    result.push_back(std::to_string(playerId));
    result.push_back(std::to_string(gameId));
    result.push_back(std::to_string(score));
    return result;
}
void Score::loadStrings(const std::vector<std::string> &rowValues)
{
    playerId = std::stoul(rowValues[0]);
    gameId = std::stoul(rowValues[1]);
    score = std::stoul(rowValues[2]);
}