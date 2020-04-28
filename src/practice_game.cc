//
// Created by GWC-CHC-07 on 4/27/2020.
//

#include "practice_game.h"

namespace myapp {

std::pair<std::string, std::string> PracticeGame::GetRandomPiece() {
  auto it = music_map.begin();
  std::next(it, rand() % music_map.size());
  return std::make_pair(it->first, it->second);
}
}