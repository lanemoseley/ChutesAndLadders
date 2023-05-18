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
  char mode;
  int numPlayers;

  void setMode();
  void setNumPlayers();

public:
  Menu();
  bool continuePlay(Player);
  int getNumPlayers();
  int rollDice();
  void welcome();
};

#endif