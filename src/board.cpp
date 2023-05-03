#include "board.h"

Board::Board() {}

void Board::printBoard(std::vector<Player> &player_list) {
  bool end_row = false;
  int i = 0;
  char symbol = 'Z';

  // Print Game Board
  for (i = 0; i < BOARD_SIZE; ++i) {
    // Getting the board symbol
    symbol = squareSymbol(i, player_list);

    // Checking for end of a row
    if ((i + 1) % 8 == 0) {
      end_row = true;
    } else {
      end_row = false;
    }

    // Printing the formatted table
    if (end_row) {
      cout << "| " << symbol << " |\n";
    }

    else if (i == BOARD_SIZE - 1) {
      cout << "| " << symbol << " |";
    }

    else {
      cout << "| " << symbol << " ";
    }
  }

  return;
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

  return;
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

char Board::squareSymbol(int check_square, std::vector<Player> &players) {
  // Checks each players location
  for (Player player : players) {
    if (player.location == check_square) {
      return player.symbol;
    }
  }

  // Checks for game-board symbol
  if (board[check_square] != '_') {
    return board[check_square];
  }

  return ' ';
}
