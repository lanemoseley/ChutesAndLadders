#include "menu.h"

Menu::Menu() : minPlayers(2), maxPlayers(4) {}

void Menu::welcome() {
  cout << setfill('-') << setw(23) << "Chutes and ladders";
  cout << setfill('-') << setw(6) << "\n";
  cout << "1, 2, 3 go up, and #, $, and ^ go down\n";

  setNumPlayers();
  setMode();
  srand(int(time(NULL)));
}

void Menu::setNumPlayers() {
  cout << "\nPlease, enter how many players: ";
  cin >> numPlayers;

  while (numPlayers < minPlayers || numPlayers > maxPlayers) {
    cout << "Please enter 2 to " << maxPlayers << " players: ";
    cin >> numPlayers;
  }
}

void Menu::setMode() {
  cout << "\nChoose which mode to play in"
       << "\n(D)ebug mode\n(P)ower mode"
       << "\nAnything else will be regular mode"
       << "\nEnter Mode: ";

  cin >> mode;
  mode = toupper(mode);
}

int Menu::getNumPlayers() { return numPlayers; }

int Menu::rollDice() {
  int roll_val = 0;

  if (mode != 'P') {
    roll_val = rand() % 6 + 1;
    cout << "Rolled a " << roll_val;
    cout << endl;
  } else { // Power Mode
    cout << "Roll: ";
    cin >> roll_val;
  }

  return roll_val;
}

bool Menu::continuePlay(Player player) {
  // Menu
  cout << endl;
  cout << setfill('-') << setw(22) << "Current player is " << player.symbol;
  cout << setfill('-') << setw(5) << "\n";

  cout << "(R)oll\n(Q)uit\n";

  char choice;
  cin >> choice;
  choice = toupper(choice);

  // Checking for valid input
  while (choice != 'R' && choice != 'Q') {
    cout << "Invalid option"
         << "\n(R)oll\n(Q)uit \n";

    cin >> choice;
    choice = toupper(choice);
  }

  if (choice == 'R') {
    return true;
  }

  return false;
}
