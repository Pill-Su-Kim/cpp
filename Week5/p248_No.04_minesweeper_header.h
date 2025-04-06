// minesweeper.h
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#define MAX_ROWS 40
#define MAX_COLS 80

void initializeBoard(int rows, int cols);
void placeMines(int rows, int cols, int mines);
void calculateAdjacency(int rows, int cols);
void printBoard(int rows, int cols, int revealAll);
void revealCell(int rows, int cols, int row, int col);
int isGameWon(int rows, int cols);

#endif
