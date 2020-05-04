//
// Created by GWC-CHC-07 on 4/21/2020.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <string>
#include <map>

namespace myapp {

class Player {
private:
  
  std::string name;
  size_t score;
  std::map<std::string, int> inventory = {
          {"Money", 500},
          {"Gas", 0},
          {"Hours Practiced", 0},
          {"Food", 0},
          {"Water", 0}
  };

public:
  Player();
  Player(std::string name, size_t score);
  
  std::string const GetName();
  void SetName(std::string name);
  size_t const GetScore();
  void SetScore(size_t score);
  std::map<std::string, int> const GetInventory();
  void AddToInventory(std::string item, int quantity);
  
};
  
} // namespace myapp

#endif //FINALPROJECT_PLAYER_H
