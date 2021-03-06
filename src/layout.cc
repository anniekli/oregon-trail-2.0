//
// Created by GWC-CHC-07 on 5/1/2020.
//

#include <cinder/app/AppBase.h>
#include "layout.h"

namespace myapp {
  Layout::Layout(std::string &checkpoint_file) {
    infile.open(cinder::app::getAssetPath(checkpoint_file), std::ios::in);

    if (infile.good()) {
      infile >> j;
      index = 0;
      startCheckpoint = j["startCheckpoint"].get<std::string>();
      std::cout << startCheckpoint << std::endl;
      endCheckpoint = j["endCheckpoint"].get<std::string>();
      current_checkpoint = Checkpoint(j["checkpoints"][index]["name"],
              j["checkpoints"][index]["description"],
              j["checkpoints"][index]["image"],
              j["checkpoints"][index]["distance"]);
    }
  }
  
  std::string Layout::GetStartCheckpoint() {
    return startCheckpoint;
  }
  
  std::string Layout::GetEndCheckpoint() {
    return endCheckpoint;
  }
  
  Checkpoint Layout::GetCurrentCheckpoint() {
    return current_checkpoint;
  }
  
  Checkpoint Layout::GetNextCheckpoint() {
    int next_index = index + 1;
    return Checkpoint(j["checkpoints"][next_index]["name"],
            j["checkpoints"][next_index]["description"],
            j["checkpoints"][next_index]["image"],
            j["checkpoints"][next_index]["distance"]);
  }
  
  void Layout::UpdateNextCheckpoint() {
    current_checkpoint = GetNextCheckpoint();
    index += 1;
  }
  
  Layout::~Layout() {
    if (infile && infile.is_open()) {
      infile.close();
    }
  }
}