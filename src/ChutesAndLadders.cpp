#include <cmath>
#include <ctime>
#include <vector>

#include "board.h"
#include "menu.h"

void activate_chute();
void activate_ladder();
void move(bool &, char, int, std::vector<int> &);
int roll_dice(char);
void run_game(Board, Menu, char, int, std::vector<int> &);

int main() {
  Board board;
  Menu menu;
  menu.welcome();
  int num_players = menu.getNumPlayers();
  char mode = menu.getMode();

  // Initializing players. A player's symbol is represented by the array index,
  // a player's position is the value at that index.
  std::vector<int> player_list(num_players, -1);

  run_game(board, menu, mode, num_players, player_list);

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

  return;
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

  return;
}

void move(Board board, bool &game_over, char mode, int current_player,
          std::vector<int> &player_list) {
  int check_val = 0;
  int move_to = 0;
  char landed_on = 'Z';
  bool hit_player = false;
  char winner = 'Z';

  // Determining which square needs to be checked
  check_val = roll_dice(mode) + player_list[current_player];
  // Checking for a chute or ladder
  board.hasChuteOrLadder(check_val, move_to, landed_on);

  // Prints messages indicating if the player landed on a chute or ladder
  if (landed_on == 'C') {
    activate_chute();
  } else if (landed_on == 'L') {
    activate_ladder();
  }

  // Checking for another player occupying the square
  hit_player = board.hasPlayer(move_to, current_player, player_list);

  if (hit_player == false) {
    // Checking that player didn't roll past the last square
    if (move_to > board.getBoardSize() - 1) {
      cout << "Rolled past the end of the board. You need an exact roll.\n";
    }
    // Checking for a winner
    else if (move_to == board.getBoardSize() - 1) {
      winner = 97 + current_player;
      cout << "Player " << winner << " won.\n";
      game_over = true;
    }
    // Updating current player's location
    else if (move_to < board.getBoardSize() - 1) {
      (player_list[current_player] = move_to);
    }
  }
  return;
}

int roll_dice(char mode) {
  int roll_val = 0;

  // Debug or Regular Mode
  if (mode != 'P') {
    roll_val = rand() % 6 + 1;
    cout << "Rolled a " << roll_val;
    cout << endl;
  }

  // Power Mode
  else {
    cout << "Roll: ";
    cin >> roll_val;
  }

  return roll_val;
}

void run_game(Board board, Menu menu, char mode, int num_players,
              std::vector<int> &player_list) {
  bool game_over = false;
  int current_player = 0;
  int i = 0;
  char roll_or_quit = 'Z';

  while (game_over == false) {
    for (i = 0; i < num_players; ++i) {
      current_player = i;

      board.printBoard(player_list);

      roll_or_quit = menu.printMenu(current_player);

      if (roll_or_quit == 'Q') {
        game_over = true;

        return;
      } else {
        move(board, game_over, mode, current_player, player_list);

        if (game_over == true) {

          return;
        }
      }
    }
  }

  return;
}
