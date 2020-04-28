//
// Created by GWC-CHC-07 on 4/22/2020.
//

#include <player.h>

namespace myapp {
  
  Player::Player(std::string name, size_t score) {
    this->name = name;
    this->score = score;
  }

  void Player::AddToInventory(std::string item, int quantity) {
    inventory.at(item) += quantity;
  }
  
  const std::map<std::string, int> Player::GetInventory() {
    return inventory;
  }
  
  const std::string Player::GetName() {
    return name;
  }
  
  void Player::SetName(std::string name) {
    this->name = name;
  }
  
  const size_t Player::GetScore() {
    return score;
  }
  

  
  
}