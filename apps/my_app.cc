// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include "cinder/Timer.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "cinder/audio/Voice.h"
#include <gflags/gflags.h>
#include <boost/algorithm/string.hpp>

#include <chrono>
#include <cmath>
#include <string>
#include <Windows.h>


namespace myapp {
  
using std::string;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using namespace choreograph;

#if defined(CINDER_COCOA_TOUCH)
  const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
  const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
  const char kNormalFont[] = "Arial";
  const char kBoldFont[] = "Arial Bold";
  const char kDifferentFont[] = "Papyrus";
#endif
  
  DECLARE_uint32(speed);
  DECLARE_string(name);

MyApp::MyApp()
  : state_{GameState::kStart},
  player_name_{FLAGS_name}

{}

void MyApp::setup() {
//  cinder::gl::Texture2d::create(getWindowWidth(), getWindowHeight());
  car_image = cinder::gl::Texture2d::create(loadImage(loadAsset("red_car.png")));
  background_image_right = cinder::gl::Texture2d::create(loadImage(loadAsset
          ("background_image_right.jpg")));
  background_image_left = cinder::gl::Texture2d::create(loadImage(loadAsset
          ("background_image_left.jpg")));

  timeline.setDefaultRemoveOnFinish(true);
  check_answer = false;
  user_input[0] = 0;
  
  mOffset = 0.0f;
// Create a Motion with a Connection to target and modify
// the Motion’s underlying Sequence.
  

}

void MyApp::update() {
  if (state_ == GameState::kTraveling) {
    if (timeline.empty()) {
      mOffset = 0.0f;
    }
    timeline.apply( &mOffset ).rampTo((float) 2 * getWindowWidth(), 10.0);
    timeline.step( 1.0 / 60.0 );
  }
  
  if (state_ == GameState::kPractice) {
  }
}

void MyApp::draw() {
  cinder::gl::clear();
  DrawBackground();
  
  if (state_ == GameState::kTraveling) {
    DrawTravel();
  }
  
  if (state_ == GameState::kMenu) {
    DrawMenu();
  }
  
  if (state_ == GameState::kPractice) {
    DrawPractice();
  }
  
  if (state_ == GameState::kInventory) {
    DrawInventory();
  }

}
  
template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);
  
  auto box = TextBox()
          .alignment(TextBox::LEFT)
          .font(cinder::Font(kNormalFont, 30))
          .size(size)
          .color(color)
          .backgroundColor(ColorA(0, 0, 0, 0))
          .text(text);
  
  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawTravel() {
  cinder::gl::clear();
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
  cinder::gl::enableAlphaBlending();
  cinder::gl::color(Color::white());
  

  Rectf coord = {mOffset, 0, getWindowWidth() + mOffset, (float) getWindowHeight()};
  Rectf coord2 = {0 - getWindowWidth() + mOffset, 0, mOffset, (float) getWindowHeight()};
  Rectf coord3 = {0 - (2 * getWindowWidth()) + mOffset, 0, mOffset - getWindowWidth(),
                  (float) getWindowHeight()};

  
  const cinder::vec2 locp = {getWindowWidth() - car_image->getWidth(),
                             getWindowHeight() - car_image->getHeight()};
  
  cinder::gl::draw(background_image_right, coord);
  cinder::gl::draw(background_image_left, coord2);
  cinder::gl::draw(background_image_right, coord3);
  
  
  cinder::gl::draw(car_image, locp);
}

void MyApp::DrawBackground() {
  cinder::gl::clear(Color(0, 0, 0));
}

void MyApp::DrawMenu() {
  
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  size_t row = 0;
  PrintText("Menu:", color, size, {center.x, (center.y - 200)});
  for (const string& option : menu_options) {
    std::stringstream ss;
    ss << std::to_string(++row) << ". " << option;
    PrintText(ss.str(), color, size, {center.x, (center.y - 200) + row * 50});
  }
}

void MyApp::DrawPractice() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  PrintText("Type the name of the piece.", color, size, {center.x, (center.y -200)});
  PrintText(user_input, color, size, {center.x, (center.y - 150)});
  
  if (check_answer) {
    if (practice_game_.CheckAnswer(user_input)) {
      PrintText("Correct!", color, size, {center.x, (center.y - 100)});
      hours_practiced_ += 5;
      practice_game_.StartNewRound();
    } else {
      PrintText("Incorrect, try again!", color, size, {center.x, (center.y -
      100)});
    }
    user_input[0] = 0;
    check_answer = false;
  }
}


void MyApp::DrawInventory() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  size_t row = 0;
  PrintText("Inventory:", color, size, {center.x, (center.y - 200)});
  for (std::pair<std::string, int> item : player_.GetInventory()) {
    std::stringstream items;
    std::stringstream quantities;
    items << item.first;
    quantities << item.second;
    PrintText(items.str(), color, size, {center.x, (center.y - 200) +
    ++row * 50});
    PrintText(quantities.str(), color, size, {center.x + 300, (center.y -
    200) + row * 50});
  }
}


void MyApp::keyDown(KeyEvent event) {
  
  // code below allows mini practice game to accept user input
  if (state_ == GameState::kPractice) {
    switch (event.getCode()) {
      case KeyEvent::KEY_RETURN: {
        check_answer = true;
        break;
      }
      case KeyEvent::KEY_BACKSPACE: {
        user_input[strlen(user_input) - 1] = 0;
        break;
      }
      default:
        check_answer = false;
        if (strlen(user_input) < kinput_length) {
          user_input[strlen(user_input) + 1] = 0;
          user_input[strlen(user_input)] = event.getChar();
          break;
        }
    }
    return;
  }
  
  // allows user to access menu and its options
  switch (event.getCode()) {
    case KeyEvent::KEY_SPACE: {
      if (state_ != GameState::kMenu) {
        state_ = GameState::kMenu;
      } else {
        state_ = GameState::kTraveling;
      }
      break;
    }
    case KeyEvent::KEY_2: {
      if (state_ == GameState::kMenu) {
        user_input[0] = 0;
        check_answer = false;
        state_ = GameState::kPractice;
        practice_game_.StartNewRound();
      }
    }
    case KeyEvent::KEY_3: {
      if (state_ == GameState::kMenu) {
        state_ = GameState::kInventory;
      }
    }
  }
}
}  // namespace myapp
