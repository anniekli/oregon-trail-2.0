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

using std::vector;
using std::string;

namespace myapp {

enum class GameState {
  kStart,
  kTraveling,
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
  const vector<string> menu_options = {
          "Map",
          "Practice",
          "Check Inventory",
          "Quit"
  };
  Player player;
  string name;
  cinder::gl::Texture2dRef car_image;
  cinder::gl::Texture2dRef background_image;
  choreograph::Output<cinder::vec2> target;
  
  
  
  void DrawBackground();
  
  void DrawInventory();
  
  void DrawTravel();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
