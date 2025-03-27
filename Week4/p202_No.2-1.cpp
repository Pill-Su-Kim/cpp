#include "p202_No.2-1 header.h"

// 5x5 배열을 0과 1로 임의로 채우는 함수
void ramdomMap(int arr[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[i][j] = rand() % 2; // 0 또는 1을 랜덤하게 할당
        }
    }
}

// 5x5 배열을 출력하는 함수
void randomMap(int arr[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int array[SIZE][SIZE];

    srand(time(NULL)); // 난수 생성기 초기화

    randomMap(array); // 배열을 랜덤하게 채움
    printf("랜덤으로 채워진 5x5 배열:\n");
    randomMap(array); // 배열 출력

    return 0;
}
