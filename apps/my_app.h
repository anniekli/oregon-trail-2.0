// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <choreograph/Choreograph.h>
#include <cinder/app/App.h>

#include <cinder/gl/gl.h>
#include "cinder/audio/Voice.h"
#include "cinder/Timer.h"
#include "leaderboard.h"

#include <random>
#include <string>
#include <vector>

using std::vector;
using std::string;

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  
  void DrawMenu();

private:
  bool draw_menu;
  bool draw_inventory;
  const vector<string> menu_options = {
          "Map",
          "Practice",
          "Check Inventory",
          "Quit"
  };
  Player player;
  string name;
  
  void DrawBackground();
  
  void DrawInventory();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
