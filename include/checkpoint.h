//
// Created by GWC-CHC-07 on 5/1/2020.
//

#ifndef FINALPROJECT_CHECKPOINT_H
#define FINALPROJECT_CHECKPOINT_H

#include <nlohmann/json.hpp>
#include <fstream>

namespace myapp {

using std::string;

class Checkpoint {
 public:
  Checkpoint(){};
  Checkpoint(std::string name, std::string description, std::string image,
          int distance);
  std::string GetName();
  std::string GetDescription();
  std::string GetImage();
  int GetDistance();

 private:
  std::string name;
  std::string description;
  std::string image;
  int distance;

};
}



#endif //FINALPROJECT_CHECKPOINT_H
