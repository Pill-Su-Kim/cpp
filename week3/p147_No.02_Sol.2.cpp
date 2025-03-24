#include <stdio.h>

int reverse(int n); //미리 함수에 대해 미리 선언

int main() {
    int num;

    // 사용자로부터 정수 입력 받기
    printf("정수를 입력하세요: ");
    scanf("%d", &num);

    // reverse 함수 호출하여 역수 출력
    printf("입력한 정수의 역수는: %d\n", reverse(num));

    return 0;
}


int reverse(int num) {
    int reversed = 0;
    while (num != 0) {
        // 마지막 자릿수를 reversed에 추가
        reversed = reversed * 10 + (num % 10);
        // num에서 마지막 자릿수를 제거
        num /= 10;
    }
    return reversed;
}
