#include "menu.h"

Menu::Menu() : minPlayers(2), maxPlayers(4) {}

void Menu::welcome() {
  cout << setfill('-') << setw(23) << "Chutes and ladders";
  cout << setfill('-') << setw(6) << "\n";
  cout << "1, 2, 3 go up, and #, $, and ^ go down\n";
}

int Menu::getNumPlayers() {
  int numPlayers = 0;

  cout << "\nPlease, enter how many players: ";
  cin >> numPlayers;

  while (numPlayers < minPlayers || numPlayers > maxPlayers) {
    cout << "Please enter 2 to " << maxPlayers << " players: ";
    cin >> numPlayers;
  }

  return numPlayers;
}

char Menu::getMode() {
  char mode = 'Z';

  cout << "\nChoose which mode to play in"
       << "\n(D)ebug mode\n(P)ower mode"
       << "\nAnything else will be regular mode"
       << "\nEnter Mode: ";

  cin >> mode;
  mode = toupper(mode);

  if (mode != 'D' && mode != 'P') {
    mode = 'R';
    srand(int(time(NULL)));
  } else {
    srand(10);
  }

  return mode;
}

char Menu::printMenu(Player player) {
  char choice = 'Z';

  // Menu
  cout << endl;
  cout << setfill('-') << setw(22) << "Current player is " << player.symbol;
  cout << setfill('-') << setw(5) << "\n";

  cout << "(R)oll\n(Q)uit\n";

  cin >> choice;
  choice = toupper(choice);

  // Checking for valid input
  while (choice != 'R' && choice != 'Q') {
    cout << "Invalid option"
         << "\n(R)oll\n(Q)uit \n";

    cin >> choice;
    choice = toupper(choice);
  }

  return choice;
}
