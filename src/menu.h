#ifndef _MENU_H_
#define _MENU_H_

#include "player.h"
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;

class Menu {
  int maxPlayers;
  int minPlayers;

public:
  Menu();
  int getNumPlayers();
  char getMode();
  char printMenu(Player);
  void welcome();
};

#endif