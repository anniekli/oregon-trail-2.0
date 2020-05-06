// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <layout.h>
#include <player.h>
#include <practice_game.h>

using myapp::Layout;
using myapp::Player;
using myapp::PracticeGame;

// test for all json-related functions

TEST_CASE("Test Layout", "[layout]") {
  std::string file = "checkpoints.json";
  Layout layout_(file);

  SECTION("Get start checkpoint") {
    REQUIRE(layout_.GetStartCheckpoint() == "Krannert Center, UIUC");
  }
  
  SECTION("Check current checkpoint is start checkpoint") {
    REQUIRE(layout_.GetCurrentCheckpoint().GetName() ==
    layout_.GetStartCheckpoint());
  }

  SECTION("Get end checkpoint") {
    REQUIRE(layout_.GetEndCheckpoint() == "Carnegie Hall, New York");
  }
  
  SECTION("Get next checkpoint") {
    REQUIRE(layout_.GetNextCheckpoint().GetName() ==
    "Chicago Symphony Orchestra, Chicago");
  }
  
  SECTION("Increment 1 checkpoint") {
    layout_.UpdateNextCheckpoint();
    REQUIRE(layout_.GetCurrentCheckpoint().GetName() == "Chicago Symphony "
                                                        "Orchestra, Chicago");
    
    REQUIRE(layout_.GetCurrentCheckpoint().GetDescription() ==
    "You arrive at the Symphony Center in Chicago, where the Chicago Symphony"
    " Orchestra performs. The raucous sounds of the city fade away as you "
    "evert the concert hall, and a beautiful symphony fills your ears.");
    
    REQUIRE(layout_.GetCurrentCheckpoint().GetImage() ==
    "https://chicagoclassicalreview"
    ".com/wp-content/uploads/Orchestra-Hall-Chicago.jpg");
    
    REQUIRE(layout_.GetCurrentCheckpoint().GetDistance() == 133);
  }
}

// test player class functions

TEST_CASE("Test Player", "[player]") {
  Player player_{"Annie"};
  
  SECTION("Get Name") {
    REQUIRE(player_.GetName() == "Annie");
  }
  
  SECTION("Get Inventory") {
    std::map<std::string, int> inventory = {
            {"Money", 300},
            {"Gas", 0},
            {"Hours Practiced", 10},
            {"Food", 0},
            {"Water", 0}
    };
    
    REQUIRE(player_.GetInventory() == inventory);
  }
  
  SECTION("Get Score") {
    REQUIRE(player_.GetScore() == 500);
  }
  
  SECTION("Add to inventory") {
    player_.AddToInventory("Food", 30);
    REQUIRE(player_.GetInventory().at("Food") == 30);
  }
  
  SECTION("Update score") {
    player_.AddToInventory("Food", 30);
    REQUIRE(player_.GetScore() == 530);
  }
  
  SECTION("Update Hours Practiced") {
    player_.AddToInventory("Hours Practiced", 30);
    REQUIRE(player_.GetScore() == 560);
  }
}

// test PracticeGame class

TEST_CASE("Test PracticeGame", "[practice-game]") {
  PracticeGame practice_game_;
  
  SECTION("Check Answer") {
    practice_game_.SetMusicPair({"", "Swan Lake"});
    REQUIRE(practice_game_.CheckAnswer("swan lake"));
  }
  
  SECTION("Get Music Piece") {
    practice_game_.SetMusicPair({"", "Swan Lake"});
    REQUIRE(practice_game_.GetMusicPiece() == "Swan Lake");
  }
}