//
// Created by GWC-CHC-07 on 5/1/2020.
//

#ifndef FINALPROJECT_LAYOUT_H
#define FINALPROJECT_LAYOUT_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <checkpoint.h>

namespace myapp {

using std::string;
using json = nlohmann::json;

class Layout {
public:
  Layout(std::string &checkpoint_file);
  std::string GetStartCheckpoint();
  std::string GetEndCheckpoint();
  void UpdateNextCheckpoint();
  Checkpoint GetCurrentCheckpoint();
  Checkpoint GetNextCheckpoint();

private:
  std::ifstream infile;
  json j;
  std::string startCheckpoint;
  std::string endCheckpoint;
  int index;
  Checkpoint current_checkpoint;
  
};
}

#endif //FINALPROJECT_LAYOUT_H
