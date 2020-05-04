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
#include "layout.h"

#include <random>
#include <string>
#include <vector>
#include <practice_game.h>
#include <nlohmann/json.hpp>

using std::vector;
using std::string;
using json = nlohmann::json;


namespace myapp {

enum class GameState {
  kStart,
  kInstructions,
  kTraveling,
  kStore,
  kCheckpoint,
  kPractice,
  kEndPractice,
  kMenu,
  kInventory
};

enum class Store {
  kFood,
  kWater,
  kGas,
  kOptions
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
  Store store_;
  Player player_;
  PracticeGame practice_game_;
  Layout layout_;
  
  const vector<string> menu_options = {
          "Continue traveling",
          "Practice",
          "Check Inventory",
          "Go to store",
          "Quit"
  };
  
  const std::map<std::string, int> store_options = {
          {"Food", 7.00},
          {"Gas", 2.50},
          {"Water", 3.00}
  };
  
  static const int kinput_length = 31;
  char user_input[kinput_length];
  const std::string player_name_;
  cinder::gl::Texture2dRef car_image;
  cinder::gl::Texture2dRef background_image_right;
  cinder::gl::Texture2dRef background_image_left;
  choreograph::Timeline timeline;
  choreograph::Output<float> mOffset;
  cinder::Timer checkpoint_timer;
  
  
  std::chrono::time_point<std::chrono::system_clock> practice_game_start_;
  std::chrono::time_point<std::chrono::system_clock> current_date_;
  
  bool check_answer;
  const size_t kpractice_time_ = 20;
  const int kspeed_ = 250;
  int hours_practiced_;
  int distance_;
  
  
  void DrawBackground();
  void DrawInventory();
  void DrawPractice();
  void DrawEndPractice() const;
  void DrawTravel();
  void DrawCheckpoint();
  void IncrementDay();
  void DrawStart();
  void DrawInstructions();
  void DrawStore();
  void BuyItem(std::string &input);
  void DrawBuyItem();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
