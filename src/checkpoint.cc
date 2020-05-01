//
// Created by GWC-CHC-07 on 5/1/2020.
//

#include "checkpoint.h"

namespace myapp {
  Checkpoint::Checkpoint(std::string name, std::string description,
                         std::string image, int distance) {
    this->name = name;
    this->description = description;
    this->image = image;
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

