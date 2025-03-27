
#include "p147_No.06_header.h"  // 헤더 파일 포함



// 게임 실행 함수 정의
void play_game() {
    int correct = 0;
    time_t start_time, current_time;

    srand(time(NULL));

    printf("=== 스피드 구구단 게임 ===\n");
    printf("제한 시간: %d초 동안 최대한 많은 문제를 맞혀보세요!\n\n", TIME_LIMIT);

    start_time = time(NULL);

    for (int i = 0; i < QUESTION_COUNT; i++) {
        int num1, num2;
        int answer, user_input;

        // 50% 확률로 한 자리 수(1~9) 또는 두 자리 수(10~99) 문제 출제
        if (rand() % 2 == 0) {  
            num1 = rand() % 9 + 1;  // 1~9
            num2 = rand() % 9 + 1;  // 1~9
        } else {
            num1 = rand() % 90 + 10; // 10~99
            num2 = rand() % 90 + 10; // 10~99
        }

        answer = num1 * num2;

        do {
            printf("%d x %d = ", num1, num2);
            scanf("%d", &user_input);

            current_time = time(NULL);
            if (current_time - start_time >= TIME_LIMIT) {
                printf("\n 제한 시간이 초과되었습니다!\n");
                printf("게임 종료! 총 맞힌 개수: %d개\n", correct);
                return;
            }

            if (user_input != answer) {
                printf("Damn !!오답! 다시 시도하세요.\n");
            }

        } while (user_input != answer);

        printf("Wow! 정답!\n");
        correct++;
    }

    printf("\n게임 종료! 총 맞힌 개수: %d개\n", correct);
}

// 메인 함수 (게임 실행)
int main() {
    play_game();
    return 0;
}
