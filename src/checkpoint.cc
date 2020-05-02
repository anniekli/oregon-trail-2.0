//
// Created by GWC-CHC-07 on 5/1/2020.
//

#include "checkpoint.h"

#include <utility>

namespace myapp {
  Checkpoint::Checkpoint(std::string name, std::string description,
                         std::string image, int distance) {
    this->name = std::move(name);
    this->description = std::move(description);
    this->image = std::move(image);
    this->distance = distance;
  }
  
  std::string Checkpoint::GetName() {
    return name;
  }
  
  std::string Checkpoint::GetDescription() {
    return description;
  }
  
  std::string Checkpoint::GetImage() {
    return image;
  }
  
  int Checkpoint::GetDistance() {
    return distance;
  }
  
}

