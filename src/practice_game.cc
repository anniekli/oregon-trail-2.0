//
// Created by GWC-CHC-07 on 4/27/2020.
//

#include <cinder/app/AppBase.h>
#include <chrono>
#include <boost/algorithm/string.hpp>
#include "practice_game.h"
#include "cinder/audio/Voice.h"


namespace myapp {

std::pair<std::string, std::string> PracticeGame::GetRandomPiece() {
  int rand_index = rand() % music_files.size();
  return std::make_pair(music_files[rand_index], music_answers[rand_index]);
}

void PracticeGame::StartNewRound() {
  music_pair = GetRandomPiece();
  cinder::audio::SourceFileRef src = cinder::audio::load
          (cinder::app::loadAsset(music_pair.first));
  music_piece = cinder::audio::Voice::create(src);
  music_piece->start();
}

void PracticeGame::EndRound() {
  music_piece->stop();
}

bool PracticeGame::CheckAnswer(std::string user_input) {
  std::string str = user_input;
  boost::to_lower(str);
  boost::to_lower(music_pair.second);
  return str == music_pair.second;
}


}