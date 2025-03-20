#include <cstdio>
#include <cmath>  // abs()를 사용하기 위해 필요

// 함수 선언
int reverse(int n);

int main() {
    printf("%d\n", reverse(12345));  // 54321
    printf("%d\n", reverse(-9876));  // -6789
    return 0;
}

// 함수 정의
int reverse(int n) {
    int reversedNumber = 0;
    int sign = (n < 0) ? -1 : 1; // 부호 저장
    n = abs(n); // 절댓값 변환

    while (n > 0) {
        reversedNumber = reversedNumber * 10 + (n % 10); // 숫자 뒤집기
        n /= 10;
    }

    return reversedNumber * sign; // 원래 부호 적용
}
