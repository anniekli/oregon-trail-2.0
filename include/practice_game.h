//
// Created by GWC-CHC-07 on 4/27/2020.
//

#ifndef FINALPROJECT_PRACTICE_GAME_H
#define FINALPROJECT_PRACTICE_GAME_H

#include <string>
#include <map>

namespace myapp {
  
class PracticeGame {
 public:
  PracticeGame(){};
  std::pair<std::string, std::string> GetRandomPiece();

 private:
  std::map<std::string, std::string> music_map = {
          {"eine_kleine.mp3", "Eine Kleine Nachtmusik"},
          {"fur_elise.mp3", "Fur Elise"},
          {"scheherazade.mp3", "Scheherazade"}
  };
  

};
}
#endif //FINALPROJECT_PRACTICE_GAME_H


