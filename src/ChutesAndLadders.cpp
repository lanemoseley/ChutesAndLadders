#include <cmath>
#include <ctime>
#include <vector>

#include "board.h"
#include "menu.h"
#include "player.h"

void activate_chute();
void activate_ladder();
void move(Board, Menu, bool &, Player &, std::vector<Player> &);
int roll_dice(char);
void run_game(Board, Menu, std::vector<Player> &);

int main() {
  Board board;
  Menu menu;
  menu.welcome();

  // Initializing players. Player's symbols are a, b, ..., z.
  std::vector<Player> players;
  for (int i = 0; i < menu.getNumPlayers(); ++i) {
    players.push_back(Player{char(i + 97)});
  }

  run_game(board, menu, players);

  return 0;
}

void activate_chute() {
  int rand_phrase = 0;

  rand_phrase = rand() % 3;

  if (rand_phrase == 0) {
    cout << "Chute: Going Down!\n";
  } else if (rand_phrase == 1) {
    cout << "Chute: Fasten your seatbelt!\n";
  } else {
    cout << "Chute: The Eagle has landed.\n";
  }
}

void activate_ladder() {
  int rand_phrase = 0;

  rand_phrase = rand() % 3;

  if (rand_phrase == 0) {
    cout << "Ladder: Going Up!\n";
  } else if (rand_phrase == 1) {
    cout << "Ladder: Up, Up and Away!\n";
  } else {
    cout << "Ladder: Houston, we have lift off.\n";
  }
}

void move(Board board, Menu menu, bool &game_over, Player &current_player,
          std::vector<Player> &players) {
  int move_to = 0;
  char landed_on = 'Z';
  bool hit_player = false;
  char winner = 'Z';

  // Determining which square needs to be checked
  int check_square = menu.rollDice() + current_player.location;
  // Checking for a chute or ladder
  board.hasChuteOrLadder(check_square, move_to, landed_on);

  // Prints messages indicating if the player landed on a chute or ladder
  if (landed_on == 'C') {
    activate_chute();
  } else if (landed_on == 'L') {
    activate_ladder();
  }

  // Checking for another player occupying the square
  hit_player = board.hasPlayer(move_to, current_player, players);

  if (hit_player == false) {
    // Checking that player didn't roll past the last square
    if (move_to > board.getBoardSize() - 1) {
      cout << "Rolled past the end of the board. You need an exact roll.\n";
    }
    // Checking for a winner
    else if (move_to == board.getBoardSize() - 1) {
      cout << "Player " << current_player.symbol << " won.\n";
      game_over = true;
    }
    // Updating current player's location
    else if (move_to < board.getBoardSize() - 1) {
      (current_player.location = move_to);
    }
  }
}

void run_game(Board board, Menu menu, std::vector<Player> &players) {
  bool game_over = false;

  while (!game_over) {
    for (Player &player : players) {
      board.printBoard(players);

      if (menu.continuePlay(player)) {
        move(board, menu, game_over, player, players);

        if (game_over) {
          return;
        }
      } else {
        return;
      }
    }
  }
}
