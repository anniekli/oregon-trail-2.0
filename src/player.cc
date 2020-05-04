//
// Created by GWC-CHC-07 on 4/22/2020.
//

#include <player.h>

namespace myapp {
  
  Player::Player() {
    score = 0;
  }
  
  Player::Player(std::string name, size_t score) {
    this->name = name;
    this->score = score;
  }

  void Player::AddToInventory(std::string item, int quantity) {
    if (inventory.at(item) + quantity > 0) {
      inventory.at(item) += quantity;
    }
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
    for (std::pair<std::string, int> pair : inventory) {
      if (pair.first == "Hours Practiced") {
        score += 2 * pair.second;
      } else {
        score += pair.second;
      }
    }
    return score;
  }
  

  
  
}