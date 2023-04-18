#include <cmath>
#include <ctime>
#include <vector>

#include "board.h"
#include "menu.h"

void activate_chute();
void activate_ladder();
void has_chute_or_ladder(int, int &, char &);
bool has_player(int, int, std::vector<int> &);
void move(bool &, char, int, std::vector<int> &);
void print_board(std::vector<int> &);
int roll_dice(char);
void run_game(Menu, char, int, std::vector<int> &);
char square_symbol(int, std::vector<int> &);

int main() {
  Menu menu;
  menu.welcome();
  int num_players = menu.getNumPlayers();
  char mode = menu.getMode();

  // Initializing players. A player's symbol is represented by the array index,
  // a player's position is the value at that index.
  std::vector<int> player_list(num_players, -1);

  run_game(menu, mode, num_players, player_list);

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

void has_chute_or_ladder(int check_val, int &move_to, char &landed_on) {
  int i = 0;

  for (i = 0; i < 3; ++i) {
    // Checking for start of chute
    if (check_val == Board::CHUTES_MAP[0][i]) {
      move_to = Board::CHUTES_MAP[1][i];
      landed_on = 'C';

      return;
    }

    // Checking for start of ladder
    else if (check_val == Board::LADDERS_MAP[0][i]) {
      move_to = Board::LADDERS_MAP[1][i];
      landed_on = 'L';

      return;
    }
  }

  // Normal square
  move_to = check_val;
  landed_on = 'N';

  return;
}

bool has_player(int move_to, int current_player,
                std::vector<int> &player_list) {
  char hit_player = 'Z';

  for (int i = 0; i < player_list.size(); ++i) {
    // Checking for player. Players can't hit themselves.
    if (move_to == player_list[i] && current_player != i) {
      hit_player = 97 + i; // ASCII value
      cout << "Hit player " << hit_player << endl;

      return true;
    }
  }

  return false;
}

void move(bool &game_over, char mode, int current_player,
          std::vector<int> &player_list) {
  int check_val = 0;
  int move_to = 0;
  char landed_on = 'Z';
  bool hit_player = false;
  char winner = 'Z';

  // Determining which square needs to be checked
  check_val = roll_dice(mode) + player_list[current_player];
  // Checking for a chute or ladder
  has_chute_or_ladder(check_val, move_to, landed_on);

  // Prints messages indicating if the player landed on a chute or ladder
  if (landed_on == 'C') {
    activate_chute();
  } else if (landed_on == 'L') {
    activate_ladder();
  }

  // Checking for another player occupying the square
  hit_player = has_player(move_to, current_player, player_list);

  if (hit_player == false) {
    // Checking that player didn't roll past the last square
    if (move_to > Board::BOARD_SIZE - 1) {
      cout << "Rolled past the end of the board. You need an exact roll.\n";
    }
    // Checking for a winner
    else if (move_to == Board::BOARD_SIZE - 1) {
      winner = 97 + current_player;
      cout << "Player " << winner << " won.\n";
      game_over = true;
    }
    // Updating current player's location
    else if (move_to < Board::BOARD_SIZE - 1) {
      (player_list[current_player] = move_to);
    }
  }
  return;
}

void print_board(std::vector<int> &player_list) {
  bool end_row = false;
  int i = 0;
  char symbol = 'Z';

  // Print Game Board
  for (i = 0; i < Board::BOARD_SIZE; ++i) {
    // Getting the board symbol
    symbol = square_symbol(i, player_list);

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

    else if (i == Board::BOARD_SIZE - 1) {
      cout << "| " << symbol << " |";
    }

    else {
      cout << "| " << symbol << " ";
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

void run_game(Menu menu, char mode, int num_players,
              std::vector<int> &player_list) {
  bool game_over = false;
  int current_player = 0;
  int i = 0;
  char roll_or_quit = 'Z';

  while (game_over == false) {
    for (i = 0; i < num_players; ++i) {
      current_player = i;

      print_board(player_list);

      roll_or_quit = menu.printMenu(current_player);

      if (roll_or_quit == 'Q') {
        game_over = true;

        return;
      } else {
        move(game_over, mode, current_player, player_list);

        if (game_over == true) {

          return;
        }
      }
    }
  }

  return;
}

char square_symbol(int check_square, std::vector<int> &player_list) {
  char symbol = ' ';

  // Checks each players location
  for (int i = 0; i < player_list.size(); ++i) {
    if (player_list[i] == check_square) {
      symbol = 97 + i; // ASCII value

      return symbol;
    }
  }

  // Checks for game-board symbol
  if (Board::STATIC_BOARD[check_square] != '_') {
    symbol = Board::STATIC_BOARD[check_square];

    return symbol;
  }

  return symbol;
}
