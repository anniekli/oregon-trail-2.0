//
// Created by GWC-CHC-07 on 5/1/2020.
//

#include "layout.h"
namespace myapp {
  Layout::Layout(std::string &checkpoint_file) {
    infile.open(checkpoint_file);
    infile >> j;
  
    index = 0;
    startCheckpoint = j["startCheckpoint"].get<std::string>();
    endCheckpoint = j["startCheckpoint"].get<std::string>();
    current_checkpoint = Checkpoint(j[index]["name"], j[index]["description"],
            j[index]["image"], j[index]["distance"]);
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
    return Checkpoint(j[next_index]["name"], j[next_index]["description"],
            j[next_index]["image"], j[next_index]["distance"]);
  }
  
  void Layout::UpdateNextCheckpoint() {
    current_checkpoint = GetNextCheckpoint();
    index += 1;
  }
}