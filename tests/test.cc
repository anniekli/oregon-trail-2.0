// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/example.h>
#include <layout.h>

using myapp::Layout;

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
    
    REQUIRE(layout_.GetCurrentCheckpoint().GetDistance() == 2043);
  }

}