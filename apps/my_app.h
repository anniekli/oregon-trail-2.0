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
  kGig,
  kCheckpoint,
  kPractice,
  kEndPractice,
  kMenu,
  kInventory,
  kLose,
  kGameOver
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
  std::string store_;
  Player player_;
  PracticeGame practice_game_;
  Layout layout_;
  LeaderBoard leaderboard_;
  
  const vector<string> menu_options = {
          "Continue traveling",
          "Go to store",
          "Play a gig",
          "Practice",
          "Check Inventory"
  };
  
  const std::map<std::string, double> store_options = {
          {"Food", 4.00},
          {"Gas", 2.00},
          {"Water", 3.00}
  };
  
  static const int kinput_length = 31;
  static const int kinput_quantity = 3;
  char user_input[kinput_length]{};
  cinder::gl::Texture2dRef car_image;
  cinder::gl::Texture2dRef background_image_right;
  cinder::gl::Texture2dRef background_image_left;
  choreograph::Timeline timeline;
  choreograph::Output<float> mOffset;
  cinder::Timer checkpoint_timer;
  std::vector<Player> top_players_;
  std::vector<Player> player_high_scores_;
  std::random_device rd;
  
  
  
  std::chrono::time_point<std::chrono::system_clock> practice_game_start_;
  std::chrono::time_point<std::chrono::system_clock> current_date_;
  
  bool check_answer{};
  const size_t kpractice_time_ = 20;
  const int kspeed_ = 250;
  const int max_gigs = 3;
  int hours_practiced_{};
  int distance_{};
  int prob;
  int gig_money;
  bool buy_item{};
  int required_hours{};
  int num_gigs;
  
  void DrawInventory();
  void DrawPractice();
  void DrawEndPractice() const;
  void DrawTravel();
  void DrawCheckpoint();
  void IncrementDay();
  void DrawStart();
  void DrawInstructions();
  void DrawStore();
  void BuyItem(int quantity, std::string &item);
  void DrawBuyItem();
  void PlayGig();
  void DrawGig();
  void DrawGameOver();
  void DrawLose();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
