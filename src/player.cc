//
// Created by GWC-CHC-07 on 4/22/2020.
//

#include <player.h>

namespace myapp {
  
  Player::Player(std::string name) {
    this->name = name;
    score = inventory.at("Money");
  }
  
  Player::Player(std::string name, size_t score) {
    this->name = name;
    this->score = score;
  }

  void Player::AddToInventory(std::string item, int quantity) {
    if (inventory.at(item) + quantity > 0) {
      inventory.at(item) += quantity;
      
      // update score;
      if (item == "Hours Practiced") {
        score += 2 * quantity;
      } else {
        score += quantity;
      }
    }
  }
  
  std::map<std::string, int> Player::GetInventory() const {
    return inventory;
  }
  
  std::string Player::GetName() const {
    return name;
  }
  
  size_t Player::GetScore() const {
    return score;
  }
  
}