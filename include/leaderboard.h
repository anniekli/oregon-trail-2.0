//
// Created by GWC-CHC-07 on 4/21/2020.
//

#ifndef FINALPROJECT_LEADERBOARD_H
#define FINALPROJECT_LEADERBOARD_H


#include <sqlite_modern_cpp.h>
#include "player.h"
#include <string>
#include <vector>

namespace myapp {
  
  class LeaderBoard {
  public:
    // Creates a new leaderboard table if it doesn't already exist.
    explicit LeaderBoard(const std::string& db_path);
    
    // Adds a player to the leaderboard.
    void AddScoreToLeaderBoard(Player&);
    
    // Returns a list of the players with the highest scores, in decreasing order.
    // The size of the list should be no greater than `limit`.
    std::vector<Player> RetrieveHighScores(const size_t limit);
    
    // Returns a list of the players with the highest scores, in decreasing order,
    // that have the same `name` as the input player name.
    // The size of the list should be no greater than `limit`.
    std::vector<Player> RetrieveHighScores(Player&, const size_t limit);
  
  private:
    sqlite::database db_;
  };
  
}  // namespace myapp


#endif //FINALPROJECT_LEADERBOARD_H
