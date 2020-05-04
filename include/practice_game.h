//
// Created by GWC-CHC-07 on 4/27/2020.
//

#ifndef FINALPROJECT_PRACTICE_GAME_H
#define FINALPROJECT_PRACTICE_GAME_H

#include <string>
#include <map>
#include <cinder/audio/Voice.h>

namespace myapp {
  
class PracticeGame {
 public:
  PracticeGame(){};
  std::pair<std::string, std::string> GetRandomPiece();
  void StartNewRound();
  void EndRound();
  bool CheckAnswer(std::string &user_input);

 private:
  std::vector<std::string> music_files = {
          "eine_kleine.mp3",
          "fur_elise.mp3",
          "scheherazade.mp3",
          "swan_lake.mp3",
          "firebird.mp3"
  };
  
  std::vector<std::string> music_answers = {
          "Eine Kleine Nachtmusik",
          "Fur Elise",
          "Scheherazade",
          "Swan Lake",
          "The Firebird"
  };
  
  cinder::audio::VoiceRef music_piece;
  std::pair<std::string, std::string> music_pair;
};
}
#endif //FINALPROJECT_PRACTICE_GAME_H


