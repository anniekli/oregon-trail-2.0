//
// Created by GWC-CHC-07 on 4/21/2020.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <string>

namespace myapp {
  
  struct Player {
    Player(const std::string& name, size_t score) : name(name), score(score) {}
    std::string name;
    size_t score;
  };
  
} // namespace myapp

#endif //FINALPROJECT_PLAYER_H
