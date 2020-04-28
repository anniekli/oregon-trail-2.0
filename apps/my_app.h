// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <choreograph/Choreograph.h>
#include <cinder/app/App.h>

#include <cinder/gl/gl.h>
#include "cinder/audio/Voice.h"
#include "cinder/Timer.h"
#include "leaderboard.h"
#include "cinder/Timeline.h"
#include "cinder/Tween.h"

#include <random>
#include <string>
#include <vector>
#include <practice_game.h>

using std::vector;
using std::string;

namespace myapp {

enum class GameState {
  kStart,
  kTraveling,
  kPractice,
  kMenu,
  kInventory
};

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  
  void DrawMenu();

private:
  GameState state_;
  Player player_;
  PracticeGame practice_game_;
  
  const vector<string> menu_options = {
          "Map",
          "Practice",
          "Check Inventory",
          "Quit"
  };
  

  static const int kinput_length = 31;
  char user_input[kinput_length];
  const std::string player_name_;
  cinder::gl::Texture2dRef car_image;
  cinder::gl::Texture2dRef background_image_right;
  cinder::gl::Texture2dRef background_image_left;
  choreograph::Timeline timeline;
  choreograph::Output<float> mOffset;
  cinder::audio::VoiceRef music_piece;
  std::pair<std::string, std::string> music_pair;
  bool check_answer;
  
  void DrawBackground();
  void DrawInventory();
  void DrawPractice();
  void DrawTravel();
  bool CheckAnswer();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
