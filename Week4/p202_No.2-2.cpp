#include "p202_No.2-2 header.h"

// 5x5 배열을 0과 1로 랜덤하게 채우는 함수
void fillArray(int map[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = rand() % 2; // 0 또는 1 랜덤 할당
        }
    }
}

// 체커보드 스타일로 출력하는 함수
void printMap(int map[SIZE][SIZE]) {
    printf("체커보드 출력:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == 1)
                printf("■ "); // 1이면 검은색 칸
            else
                printf("□ "); // 0이면 흰색 칸
        }
        printf("\n");
    }
}

int main() {
    int map[SIZE][SIZE];

    srand(time(NULL)); // 난수 생성기 초기화

    fillArray(map); // 2차원 배열을 랜덤하게 채우기
    printMap(map); // 체커보드 출력

    return 0;
}
