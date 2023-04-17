#ifndef _BOARD_H_
#define _BOARD_H_

namespace Board {
static const int BOARD_SIZE = 40;
static const char STATIC_BOARD[BOARD_SIZE] = {
    '_', '_', '_', '#', '1', '_', '2', '_', '_', '_', '_', '1', '$', '_',
    '_', '_', '_', '#', '_', '3', '_', '_', '_', '_', '_', '_', '%', '2',
    '_', '_', '$', '_', '_', '_', '_', '%', '3', '_', '_', '_'};
static const int CHUTES_MAP[2][3] = {3, 12, 26, 17, 30, 35};
static const int LADDERS_MAP[2][3] = {11, 27, 36, 4, 6, 19};
} // namespace Board

#endif