#include "board.h"

Board::Board() {}

void Board::printBoard(std::vector<Player> &player_list) {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    char symbol = symbolAtLocation(i, player_list);
    bool end_of_row = (i + 1) % 8 == 0 ? true : false;
    bool end_of_last_row = i == BOARD_SIZE - 1 ? true : false;

    cout << "| " << symbol;

    if (end_of_row) {
      cout << " |\n";
    } else if (end_of_last_row) {
      cout << " |";
    } else {
      cout << " ";
    }
  }
}

int Board::getBoardSize() { return BOARD_SIZE; }

void Board::hasChuteOrLadder(int check_val, int &move_to, char &landed_on) {
  for (int i = 0; i < 3; ++i) {
    // Checking for start of chute
    if (check_val == chutes[0][i]) {
      move_to = chutes[1][i];
      landed_on = 'C';

      return;
    }

    // Checking for start of ladder
    else if (check_val == ladders[0][i]) {
      move_to = ladders[1][i];
      landed_on = 'L';

      return;
    }
  }

  // Normal square
  move_to = check_val;
  landed_on = 'N';
}

bool Board::hasPlayer(int move_to, Player current_player,
                      std::vector<Player> &players) {
  for (Player player : players) {
    // Checking for player. Players can't hit themselves.
    if (move_to == player.location && current_player.symbol != player.symbol) {
      cout << "Hit player " << player.symbol << endl;
      return true;
    }
  }

  return false;
}

char Board::symbolAtLocation(int location, std::vector<Player> &players) {
  // Checks each players location
  for (Player player : players) {
    if (player.location == location) {
      return player.symbol;
    }
  }

  // Checks for game-board symbol
  if (board[location] != '_') {
    return board[location];
  }

  return ' ';
}
