#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

// 5x5 배열을 0과 1로 랜덤하게 채우는 함수
void fillArray(int map[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = rand() % 2; // 0 또는 1 랜덤 할당
        }
    }
}

// 5x5 배열을 출력하는 함수
void printMap(int map[SIZE][SIZE]) {
    printf("체커보드 출력:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

// 가로, 세로, 대각선이 같은 숫자로 채워진 부분을 찾아 표시하는 함수
void checkLines(int map[SIZE][SIZE]) {
    int row, col;

    printf("\n일치하는 라인을 *로 표시한 체커보드:\n");

    // 복사 배열 생성
    char display[SIZE][SIZE];

    // 기본 배열 복사
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            display[row][col] = map[row][col] + '0'; // 0과 1을 문자로 변환
        }
    }

    // 가로 확인
    for (row = 0; row < SIZE; row++) {
        int first = map[row][0];
        int same = 1;
        for (col = 1; col < SIZE; col++) {
            if (map[row][col] != first) {
                same = 0;
                break;
            }
        }
        if (same) {
            for (col = 0; col < SIZE; col++) {
                display[row][col] = '*';
            }
        }
    }

    // 세로 확인
    for (col = 0; col < SIZE; col++) {
        int first = map[0][col];
        int same = 1;
        for (row = 1; row < SIZE; row++) {
            if (map[row][col] != first) {
                same = 0;
                break;
            }
        }
        if (same) {
            for (row = 0; row < SIZE; row++) {
                display[row][col] = '*';
            }
        }
    }

    // 대각선 확인 (왼쪽 위 → 오른쪽 아래)
    int first = map[0][0], same = 1;
    for (row = 1; row < SIZE; row++) {
        if (map[row][row] != first) {
            same = 0;
            break;
        }
    }
    if (same) {
        for (row = 0; row < SIZE; row++) {
            display[row][row] = '*';
        }
    }

    // 대각선 확인 (오른쪽 위 → 왼쪽 아래)
    first = map[0][SIZE - 1];
    same = 1;
    for (row = 1; row < SIZE; row++) {
        if (map[row][SIZE - 1 - row] != first) {
            same = 0;
            break;
        }
    }
    if (same) {
        for (row = 0; row < SIZE; row++) {
            display[row][SIZE - 1 - row] = '*';
        }
    }

    // 수정된 배열 출력
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            printf("%c ", display[row][col]);
        }
        printf("\n");
    }
}

int main() {
    int map[SIZE][SIZE];

    srand(time(NULL)); // 난수 생성기 초기화

    fillArray(map); // 2차원 배열 랜덤 채우기
    printMap(map); // 기본 체커보드 출력
    checkLines(map); // 일치하는 줄을 찾아 *로 표시한 결과 출력

    return 0;
}
