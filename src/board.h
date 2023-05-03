#ifndef _BOARD_H_
#define _BOARD_H_

#include "player.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class Board {
  static const int BOARD_SIZE = 40;
  const char board[BOARD_SIZE] = {
      '_', '_', '_', '#', '1', '_', '2', '_', '_', '_', '_', '1', '$', '_',
      '_', '_', '_', '#', '_', '3', '_', '_', '_', '_', '_', '_', '%', '2',
      '_', '_', '$', '_', '_', '_', '_', '%', '3', '_', '_', '_'};
  const int chutes[2][3] = {3, 12, 26, 17, 30, 35};
  const int ladders[2][3] = {11, 27, 36, 4, 6, 19};
  char symbolAtLocation(int, std::vector<Player> &);

public:
  Board();
  int getBoardSize();
  void hasChuteOrLadder(int, int &, char &);
  bool hasPlayer(int, Player, std::vector<Player> &);
  void printBoard(std::vector<Player> &);
};

#endif