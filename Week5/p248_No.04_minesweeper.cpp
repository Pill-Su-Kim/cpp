// minesweeper.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "p248_No.04_minesweeper_header.h"

static int MineMapMask[MAX_ROWS][MAX_COLS];   // 0: 안 연 셀, 1: 연 셀, 2: 깃발(P)
static int MineMapLabel[MAX_ROWS][MAX_COLS];  // -1: 지뢰, 0~8: 주변 지뢰 수

void initializeBoard(int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            MineMapMask[i][j] = 0;
            MineMapLabel[i][j] = 0;
        }
}

void placeMines(int rows, int cols, int mines) {
    int placed = 0;
    while (placed < mines) {
        int r = rand() % rows;
        int c = rand() % cols;
        if (MineMapLabel[r][c] != -1) {
            MineMapLabel[r][c] = -1; // 지뢰 매설
            placed++;
        }
    }
}

void calculateAdjacency(int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            if (MineMapLabel[i][j] == -1) continue;
            int count = 0;
            for (int dr = -1; dr <= 1; ++dr)
                for (int dc = -1; dc <= 1; ++dc) {
                    int nr = i + dr;
                    int nc = j + dc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
                        if (MineMapLabel[nr][nc] == -1) count++;
                }
            MineMapLabel[i][j] = count;
        }
}

void printBoard(int rows, int cols, int revealAll) {
    printf("    ");
    for (int j = 0; j < cols; ++j)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < rows; ++i) {
        printf("%2d ", i);
        for (int j = 0; j < cols; ++j) {
            if (revealAll || MineMapMask[i][j] == 1) {
                if (MineMapLabel[i][j] == -1)
                    printf(" * ");
                else
                    printf(" %d ", MineMapLabel[i][j]);
            } else if (MineMapMask[i][j] == 2) {
                printf(" P ");
            } else {
                printf(" # ");
            }
        }
        printf("\n");
    }
}

void revealCell(int rows, int cols, int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) return;
    if (MineMapMask[row][col] == 1 || MineMapMask[row][col] == 2) return;
    MineMapMask[row][col] = 1;

    if (MineMapLabel[row][col] == 0) {
        for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <= 1; ++dc)
                if (dr != 0 || dc != 0)
                    revealCell(rows, cols, row + dr, col + dc);
    }
}

int isGameWon(int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (MineMapLabel[i][j] != -1 && MineMapMask[i][j] != 1)
                return 0;
    return 1;
}

int main() {
    int rows, cols, mines;
    srand((unsigned int)time(NULL));

    printf("Enter map size (rows cols): ");
    scanf("%d %d", &rows, &cols);
    if (rows <= 0 || rows > MAX_ROWS || cols <= 0 || cols > MAX_COLS) {
        printf("Invalid size! Max is %d x %d.\n", MAX_ROWS, MAX_COLS);
        return 1;
    }

    printf("Enter number of mines: ");
    scanf("%d", &mines);
    if (mines <= 0 || mines >= rows * cols) {
        printf("Invalid number of mines.\n");
        return 1;
    }

    initializeBoard(rows, cols);
    placeMines(rows, cols, mines);
    calculateAdjacency(rows, cols);

    char input[100];
    while (1) {
        printBoard(rows, cols, 0);
        printf("Enter command (ex: 20 10 or p 20 10): ");
        scanf(" %[^\n]", input);

        int row, col;
        if (input[0] == 'p' || input[0] == 'P') {
            if (sscanf(input + 1, "%d %d", &col, &row) == 2) {
                if (row >= 0 && row < rows && col >= 0 && col < cols) {
                    if (MineMapMask[row][col] == 0)
                        MineMapMask[row][col] = 2; // 깃발 세움
                    else if (MineMapMask[row][col] == 2)
                        MineMapMask[row][col] = 0; // 깃발 제거
                } else {
                    printf("Invalid position.\n");
                }
            }
        } else {
            if (sscanf(input, "%d %d", &col, &row) == 2) {
                if (row >= 0 && row < rows && col >= 0 && col < cols) {
                    if (MineMapLabel[row][col] == -1) {
                        printf("Boom! You hit a mine.\n");
                        printBoard(rows, cols, 1);
                        break;
                    } else {
                        revealCell(rows, cols, row, col);
                    }
                } else {
                    printf("Invalid position.\n");
                }
            }
        }

        if (isGameWon(rows, cols)) {
            printf("Congratulations! You cleared the minefield!\n");
            printBoard(rows, cols, 1);
            break;
        }
    }

    return 0;
}
