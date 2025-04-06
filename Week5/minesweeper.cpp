// minesweeper.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h"

// 함수 정의
void initializeBoard(Cell board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            board[i][j].isMine = 0;
            board[i][j].isRevealed = 0;
            board[i][j].adjacentMines = 0;
        }
    }
}

void placeMines(Cell board[ROWS][COLS]) {
    int placed = 0;
    while (placed < MINES) {
        int r = rand() % ROWS;
        int c = rand() % COLS;
        if (!board[r][c].isMine) {
            board[r][c].isMine = 1;
            placed++;
        }
    }
}

void calculateAdjacency(Cell board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j].isMine) continue;
            int count = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    int nr = i + dr;
                    int nc = j + dc;
                    if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS) {
                        if (board[nr][nc].isMine) count++;
                    }
                }
            }
            board[i][j].adjacentMines = count;
        }
    }
}

void printBoard(Cell board[ROWS][COLS], int revealAll) {
    printf("   ");
    for (int i = 0; i < COLS; ++i) {
        printf("%2d", i);
    }
    printf("\n");

    for (int i = 0; i < ROWS; ++i) {
        printf("%2d ", i);
        for (int j = 0; j < COLS; ++j) {
            if (revealAll || board[i][j].isRevealed) {
                if (board[i][j].isMine) {
                    printf(" *");
                } else {
                    printf(" %d", board[i][j].adjacentMines);
                }
            } else {
                printf(" #");
            }
        }
        printf("\n");
    }
}

void revealCell(Cell board[ROWS][COLS], int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) return;
    if (board[row][col].isRevealed) return;
    board[row][col].isRevealed = 1;

    if (board[row][col].adjacentMines == 0 && !board[row][col].isMine) {
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr != 0 || dc != 0) {
                    revealCell(board, row + dr, col + dc);
                }
            }
        }
    }
}

int isGameWon(Cell board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (!board[i][j].isMine && !board[i][j].isRevealed) {
                return 0;
            }
        }
    }
    return 1;
}

// 메인 함수
int main() {
    Cell board[ROWS][COLS];
    int row, col;

    srand((unsigned int)time(NULL));
    initializeBoard(board);
    placeMines(board);
    calculateAdjacency(board);

    while (1) {
        printBoard(board, 0);
        printf("Enter row and column (ex: 1 3): ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (board[row][col].isMine) {
            printf("Boom! You hit a mine.\n");
            printBoard(board, 1);
            break;
        }

        revealCell(board, row, col);

        if (isGameWon(board)) {
            printf("Congratulations! You've cleared the minefield!\n");
            printBoard(board, 1);
            break;
        }
    }

    return 0;
}

