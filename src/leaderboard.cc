//
// Created by GWC-CHC-07 on 4/21/2020.
//

#include "leaderboard.h"
#include "player.h"
#include <sqlite_modern_cpp.h>
#include <vector>

namespace myapp {
  
  using std::string;
  using std::vector;
  
  LeaderBoard::LeaderBoard(const string& db_path) : db_{db_path} {
    db_ << "CREATE TABLE if not exists leaderboard (\n"
           "  name  TEXT NOT NULL,\n"
           "  score INTEGER NOT NULL \n"
           ");";
  }
  
  void LeaderBoard::AddScoreToLeaderBoard(const Player& player) {
    db_ << "INSERT INTO leaderboard (name,score,time) VALUES (?,?,?);"
        << player.name
        << player.score;
  }
  
  vector<Player> GetPlayers(sqlite::database_binder* rows) {
    vector<Player> players;
    
    for (auto&& row : *rows) {
      string name;
      size_t score;
      row >> name >> score;
      Player player = {name, score};
      players.push_back(player);
    }
    
    return players;
  }
  
  vector<Player> LeaderBoard::RetrieveHighScores(const size_t limit) {
    auto rows = db_ << "SELECT * FROM leaderboard ORDER BY score DESC "
                       "LIMIT ?;"
                    << limit;
    return GetPlayers(&rows);
  }
  
  vector<Player> LeaderBoard::RetrieveHighScores(const Player& player,
                                                 const size_t limit) {
    auto rows = db_ << "SELECT * FROM leaderboard WHERE name = ? "
                       "ORDER BY score DESC LIMIT ?;"
                    << player.name
                    << limit;
    return GetPlayers(&rows);
  }
  
}  // namespace snake