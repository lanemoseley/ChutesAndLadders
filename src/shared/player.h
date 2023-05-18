#ifndef _PLAYER_H_
#define _PLAYER_H_

struct Player {
  int location;
  char symbol;

  Player(char symbol) : location(-1), symbol(symbol) {}
};

#endif