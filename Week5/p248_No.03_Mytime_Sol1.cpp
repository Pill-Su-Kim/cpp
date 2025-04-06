#include <stdio.h>
#include "p248_No.03_Mytime_header_Sol1.h"  // 구조체랑 함수 선언 불러오기

// 함수 정의
MyTime addTime(MyTime t1, MyTime t2) {
    MyTime result;

    result.millisecond = t1.millisecond + t2.millisecond;
    result.second = t1.second + t2.second;
    result.minute = t1.minute + t2.minute;
    result.hour = t1.hour + t2.hour;

    if (result.millisecond >= 1000) {
        result.second += result.millisecond / 1000;
        result.millisecond %= 1000;
    }
    if (result.second >= 60) {
        result.minute += result.second / 60;
        result.second %= 60;
    }
    if (result.minute >= 60) {
        result.hour += result.minute / 60;
        result.minute %= 60;
    }
    
    return result;
}

// main 함수
int main() {
    MyTime t1 = {1, 59, 58, 900};
    MyTime t2 = {0, 0, 2, 300};

    MyTime sum = addTime(t1, t2);

    printf("Result: %02d:%02d:%02d.%03d\n",
           sum.hour, sum.minute, sum.second, sum.millisecond);

    return 0;
}
