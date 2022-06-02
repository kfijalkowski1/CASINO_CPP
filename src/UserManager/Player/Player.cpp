#include "Player.h"

const std::array<std::string, 4> Player::correctFieldNames = {
    "id", "name", "password", "cash"};

Player::Player() {}

Player::Player(unsigned int id, std::string name, std::string password)
    : id(id), name(name), password(password), cash(1000)
{
}

std::vector<std::string> Player::toStrings()
{
    std::vector<std::string> result;
    result.push_back(std::to_string(id));
    result.push_back(name);
    result.push_back(password);
    result.push_back(std::to_string(cash));
    return result;
}
void Player::loadStrings(const std::vector<std::string> &rowValues)
{
    id = std::stoul(rowValues[0]);
    name = rowValues[1];
    password = rowValues[2];
    cash = std::stoul(rowValues[3]);
}

// implement compere operators

bool Player::operator==(Player const &p) const noexcept { return id == p.id; }