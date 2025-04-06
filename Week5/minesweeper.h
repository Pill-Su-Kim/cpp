// minesweeper.h
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#define ROWS 9
#define COLS 9
#define MINES 10

typedef struct {
    int isMine;
    int isRevealed;
    int adjacentMines;
} Cell;

void initializeBoard(Cell board[ROWS][COLS]);
void placeMines(Cell board[ROWS][COLS]);
void calculateAdjacency(Cell board[ROWS][COLS]);
void printBoard(Cell board[ROWS][COLS], int revealAll);
void revealCell(Cell board[ROWS][COLS], int row, int col);
int isGameWon(Cell board[ROWS][COLS]);

#endif // MINESWEEPER_H
