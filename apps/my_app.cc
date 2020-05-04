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
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


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
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using json = nlohmann::json;
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
  DECLARE_string(file);
  
  
  MyApp::MyApp()
  : state_{GameState::kStart},
  player_name_{FLAGS_name},
  layout_{FLAGS_file}

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
  distance_ = layout_.GetCurrentCheckpoint().GetDistance();
  store_ = "";
  
  std::cout << layout_.GetCurrentCheckpoint().GetName() << std::endl;

}

void MyApp::update() {
  if (state_ == GameState::kTraveling) {
    if (timeline.empty()) {
      mOffset = 0.0f;
    }
    timeline.apply( &mOffset ).rampTo((float) 2 * getWindowWidth(), 10.0);
    timeline.step( 1.0 / 60.0 );
    
    // increment day every second
    if (checkpoint_timer.getSeconds() >= 1) {
      checkpoint_timer.stop();
      checkpoint_timer.start();
      IncrementDay();
    }
    
  
  }
  
  if (state_ == GameState::kPractice) {
    if (duration_cast<std::chrono::seconds>
                (system_clock::now() - practice_game_start_).count() >=
                kpractice_time_) {
      state_ = GameState::kEndPractice;
      practice_game_.EndRound();
      player_.AddToInventory("Hours Practiced", hours_practiced_);
    }
  }
}

void MyApp::draw() {
  cinder::gl::clear();
  DrawBackground();
  
  switch (state_) {
    case GameState::kStart: {
      DrawStart();
      break;
    }
    
    case GameState::kInstructions: {
      DrawInstructions();
      break;
    }
  
    case GameState::kStore: {
      if (store_.empty()) {
        DrawStore();
      } else {
        DrawBuyItem();
      }
      break;
    }
  
    case GameState::kGig: {
      DrawGig();
      break;
    }
    
    case GameState::kCheckpoint: {
      DrawCheckpoint();
      break;
    }
    
    case GameState::kTraveling: {
      DrawTravel();
      break;
    }
  
    case GameState::kMenu: {
      DrawMenu();
      break;
    }
  
    case GameState::kPractice: {
      DrawPractice();
      break;
    }
  
    case GameState::kEndPractice: {
      DrawEndPractice();
      break;
    }
  
    case GameState::kInventory: {
      DrawInventory();
      break;
    }
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

void MyApp::IncrementDay() {
  if (distance_ + kspeed_ < layout_.GetCurrentCheckpoint().GetDistance()) {
    distance_ += kspeed_;
    player_.AddToInventory("Gas", - (kspeed_ / 10));
  } else {
    player_.AddToInventory("Gas",- ((layout_.GetCurrentCheckpoint()
    .GetDistance() - distance_) / 10));
    distance_ = layout_.GetCurrentCheckpoint().GetDistance();
  }
  player_.AddToInventory("Food", -1);
  player_.AddToInventory("Water", -1);
  current_date_ += std::chrono::hours(24);
}

void MyApp::DrawStart() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  PrintText("Welcome to the game! Press ENTER to begin.", color, size, {center
  .x, (center.y - 200)});

}

void MyApp::DrawInstructions() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 500};
  const Color color = Color::white();
  
  
  PrintText("You are about to embark on a journey of a lifetime. You have "
            "just graduated from UIUC's music school, and having been "
            "planning this trip for years. You will be performing in the most"
            " famous music venues across the globe.", color, size, {center.x,
             center.y - 100});
  
  PrintText("Before you begin, you need to stop at a few stores. You already "
            "have your instrument and music. Instead of staying in hotels, "
            "you will travel and live in an RV to save money -- lucky for "
            "you, you managed to get one from a friend! You already own "
            "most supplies you need. Now, you need to buy:", color, size,
            {center.x, center.y + 100});
  
  size_t row = 0;
  for (const std::pair<std::string, double> option: store_options) {
    std::stringstream ss;
    ss << "- " << option.first;
    PrintText(ss.str(), color, size, {center.x, (center.y + 300) + ++row * 50});
  }
  
  PrintText("Press ENTER to continue to the store", color, size,
          {center.x,(center.y + 300) + ++row * 50});
}

void MyApp::DrawTravel() {
  cinder::gl::clear();
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
  cinder::gl::enableAlphaBlending();
  cinder::gl::color(Color::white());
  

//  Rectf coord = {mOffset, 0, getWindowWidth() + mOffset, (float) getWindowHeight()};
//  Rectf coord2 = {0 - getWindowWidth() + mOffset, 0, mOffset, (float) getWindowHeight()};
//  Rectf coord3 = {0 - (2 * getWindowWidth()) + mOffset, 0, mOffset - getWindowWidth(),
//                  (float) getWindowHeight()};
//
//
//  const cinder::vec2 locp = {getWindowWidth() - car_image->getWidth(),
//                             getWindowHeight() - car_image->getHeight()};
//
//  cinder::gl::draw(background_image_right, coord);
//  cinder::gl::draw(background_image_left, coord2);
//  cinder::gl::draw(background_image_right, coord3);
//
//  cinder::gl::draw(car_image, locp);
  
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  auto in_time_t = std::chrono::system_clock::to_time_t(current_date_);
  
  std::stringstream ss;
  ss << "Date: " << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  PrintText(ss.str(), color, size, {center.x - 500, center.y});
  std::cout << ss.str() << std::endl;
}

void MyApp::DrawBackground() {
  cinder::gl::clear(Color(0, 0, 0));
}

void MyApp::DrawMenu() {
  
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  size_t row = 0;
  
  PrintText("You may:", color, size, {center.x, (center.y - 200)});
  
  for (const string& option : menu_options) {
    std::stringstream ss;
    if ((distance_ != layout_.GetCurrentCheckpoint().GetDistance()
      && option != "Go to store")
      || (distance_ == layout_.GetCurrentCheckpoint().GetDistance()
      && option != "Play a gig")) {
      
      // if not at a checkpoint, print out the option to play a gig
      // if at a checkpoint, print out the option to go to the store
      ss << std::to_string(++row) << ". " << option;
      PrintText(ss.str(), color, size, {center.x, (center.y - 200) + row * 50});
    }
  }
}

void MyApp::DrawStore() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  
  size_t row = 0;
  PrintText("Store:", color, size, {center.x, (center.y - 200)});
  for (std::pair<std::string, double> option : store_options) {
    std::stringstream items;
    std::stringstream price;
    items << std::to_string(++row) << ". " << option.first;
    price << "$" << option.second;
    PrintText(items.str(), color, size, {center.x, (center.y - 200) +
                                                   row * 50});
    PrintText(price.str(), color, size, {center.x + 300, (center.y -
                                                               200) + row * 50});
  }
  
  std::stringstream ss;
  ss << "Money: " << player_.GetInventory().at("Money");
  PrintText(ss.str(), color, size, {center.x, (center.y -
                                                        200) + ++row * 50});
  PrintText("Press SPACE BAR to return to menu", color, size,
            {center.x, (center.y - 200) + ++row * 50});
}

void MyApp::DrawBuyItem() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  std::stringstream ss;
  ss << "How much " << store_ << " would you like to buy?";
  PrintText(ss.str(), color, size, {center.x, (center.y - 200)});
  PrintText(user_input, color, size, {center.x, (center.y - 150)});
}

void MyApp::BuyItem(int quantity, std::string &item) {
  int price = store_options.at(item);
  if (price * quantity <= player_.GetInventory().at("Money")) {
    player_.AddToInventory("Money", - (price * quantity));
    player_.AddToInventory(item, quantity);
  }
}

void MyApp::DrawGig() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  if (prob == 0) {
    PrintText("You got the gig!", color, size, center);
    std::stringstream ss;
    ss << "You earned $" << gig_money << " from this gig.";
    PrintText(ss.str(), color, size, {center.x, (center.y + 100)});
  } else {
    PrintText("Sorry, you didn't get the gig. Better luck next time!", color,
            size, center);
  }
}

void MyApp::PlayGig() {
  prob = rand() % 5;
  gig_money = rand() % 450 + 50;
  
  if (prob == 0) {
    player_.AddToInventory("Money", gig_money);
  }
  
  std::cout << prob << std::endl;
  std::cout << gig_money << std::endl;
  
}

void MyApp::DrawCheckpoint() {
  Checkpoint checkpoint = layout_.GetCurrentCheckpoint();
  
  cinder::Url url(checkpoint.GetImage());
  cinder::gl::Texture2dRef image = cinder::gl::Texture2d::create(loadImage(
          loadUrl(url)));

  if (image) {
    cinder::gl::draw(image, getWindowBounds());
  }
  
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::black();
  
  PrintText(checkpoint.GetName(), color, size, {center.x, center.y + 100});
  PrintText(checkpoint.GetDescription(), color, size, center);
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

void MyApp::DrawEndPractice() const {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  
  std::stringstream end_message;
  end_message << "You practiced " << hours_practiced_ << " hours.";
  PrintText(end_message.str(), color, size, {center.x, (center.y - 200)});
  PrintText("Press SPACE BAR to continue", color, size, {center.x, (center.y -
  150)});
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
  
  PrintText("Press SPACE BAR to return to menu", color, size,
          {center.x, (center.y - 200) + ++row * 50});
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
  
  if (state_ == GameState::kStore && store_.empty()) {
    switch (event.getCode()) {
      case KeyEvent::KEY_1: {
        store_ = "Food";
        break;
      }
  
      case KeyEvent::KEY_2: {
        store_ = "Gas";
        break;
      }
  
      case KeyEvent::KEY_3: {
        store_ = "Water";
        break;
      }
      
      case KeyEvent::KEY_SPACE: {
        state_ = GameState::kMenu;
      }
    }
    return;
  }
  
  // allows user to buy items from store
  if (!store_.empty()) {
    switch (event.getCode()) {
      case KeyEvent::KEY_SPACE: {
        store_ = "";
        break;
      }
      
      case KeyEvent::KEY_RETURN: {
        if (strlen(user_input) > 0) {
          BuyItem(atoi(user_input), store_);
          user_input[0] = 0;
          store_ = "";
        }
        break;
      }
  
      case KeyEvent::KEY_BACKSPACE: {
        user_input[strlen(user_input) - 1] = 0;
        break;
      }
  
      default:
        if (event.getChar() >= '0' && event.getChar() <= '9'
            && strlen(user_input) < kinput_quantity) {
          user_input[strlen(user_input) + 1] = 0;
          user_input[strlen(user_input)] = event.getChar();
          break;
        }
    }
    return;
  }
  
  // allows user to select different menu options
  if (state_ == GameState::kMenu) {
    switch (event.getCode()) {
      
      case KeyEvent::KEY_1: {
        state_ = GameState::kTraveling;
        checkpoint_timer.resume();
        
        // if you are at a checkpoint and are now leaving, update next
        // checkpoint
        if (distance_ == layout_.GetCurrentCheckpoint().GetDistance()) {
          layout_.UpdateNextCheckpoint();
          distance_ = 0;
        }
        
        break;
      }
  
      case KeyEvent::KEY_2: {
        if (distance_ == layout_.GetCurrentCheckpoint().GetDistance()) {
          state_ = GameState::kStore;
          user_input[0] = 0;
      
        } else {
          PlayGig();
          state_ = GameState::kGig;
        }
        break;
      }
  
      case KeyEvent::KEY_3: {
        hours_practiced_ = 0;
        user_input[0] = 0;
        check_answer = false;
        state_ = GameState::kPractice;
        practice_game_start_ = system_clock::now();
        practice_game_.StartNewRound();
        break;
      }
  
      case KeyEvent::KEY_4: {
        state_ = GameState::kInventory;
        break;
      }
      
      case KeyEvent::KEY_5: {
        //quit
      }

    }
    return;
  }
  
  // allows user to access menu or exit practice
  switch (event.getCode()) {
    case KeyEvent::KEY_SPACE: {
    
      if (state_ == GameState::kEndPractice) {
        state_ = GameState::kMenu;
      
      } else if (state_ != GameState::kMenu && state_ != GameState::kStart
        && state_ != GameState::kInstructions) {
        state_ = GameState::kMenu;
        checkpoint_timer.stop();
      }
      break;
    }
  
    case KeyEvent::KEY_RETURN: {
      if (state_ == GameState::kStart) {
        state_ = GameState::kInstructions;
      
      } else if (state_ == GameState::kInstructions) {
        state_ = GameState::kStore;
      
      } else if (state_ == GameState::kStore &&
                 layout_.GetStartCheckpoint() ==
                 layout_.GetCurrentCheckpoint().GetName()) {
      
        // if you are just starting the game and leaving the first
        // checkpoint, set the date leaving to now.
        state_ = GameState::kTraveling;
        current_date_ = system_clock::now();
      }
    }
  }
}


  
}  // namespace myapp
