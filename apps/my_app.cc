// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <choreograph/Choreograph.h>

#include <cinder/app/App.h>

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include "cinder/Timer.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "cinder/audio/Voice.h"
#include "cinder/Timeline.h"

#include <algorithm>
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

MyApp::MyApp()
  : state_{GameState::kStart}
{}

void MyApp::setup() {
//  cinder::gl::Texture2d::create(getWindowWidth(), getWindowHeight());
  car_image = cinder::gl::Texture2d::create(loadImage(loadAsset("red_car.png")));
  background_image = cinder::gl::Texture2d::create(loadImage(loadAsset
          ("background_image_right.jpg")));


  
  
  target = {0, getWindowWidth()};
// Create a Motion with a Connection to target and modify
// the Motion’s underlying Sequence.

}

void MyApp::update() {
  choreograph::Timeline timeline;
  
  timeline.apply( &target )
          .then<RampTo>( cinder::vec2( getWindowWidth(), 2 * getWindowWidth()
          ), 5.0);
  timeline.step( 1.0 / 60.0 );
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
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
  cinder::gl::enableAlphaBlending();
  cinder::gl::color(Color::white());
  

  float x = target.value().x;
  float x2 = target.value().y;
  Rectf coord = {x, 0, x2, (float) getWindowHeight()};
  const cinder::vec2 locp = {100, 100};
  
  cinder::gl::draw(background_image, coord);
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
  for (const string option : menu_options) {
    std::stringstream ss;
    ss << std::to_string(++row) << ". " << option;
    PrintText(ss.str(), color, size, {center.x, (center.y - 200) + row * 50});
  }
}

void MyApp::DrawInventory() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  size_t row = 0;
  PrintText("Inventory:", color, size, {center.x, (center.y - 200)});
  for (std::pair<std::string, int> item : player.GetInventory()) {
    std::stringstream items;
    std::stringstream quantities;
    items << std::to_string(++row) << ". " << item.first;
    quantities << item.second;
    PrintText(items.str(), color, size, {center.x, (center.y - 200) +
    row * 50});
    PrintText(quantities.str(), color, size, {center.x + 300, (center.y -
    200) + row * 50});
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_SPACE: {
      if (state_ != GameState::kMenu) {
        state_ = GameState::kMenu;
      } else {
        state_ = GameState::kTraveling;
      }
      break;
    }
    case KeyEvent::KEY_3: {
      if (state_ == GameState::kMenu) {
        state_ = GameState::kInventory;
      }
    }
  }
}


}  // namespace myapp
