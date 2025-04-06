#include <stdio.h>
#include "p248_No.03_Mytime_header_Sol3.h"

// 함수 정의
void addTime(MyTime t1, MyTime t2, MyTime *t3) {
    t3->millisecond = t1.millisecond + t2.millisecond;
    t3->second = t1.second + t2.second;
    t3->minute = t1.minute + t2.minute;
    t3->hour = t1.hour + t2.hour;

    if (t3->millisecond >= 1000) {
        t3->second += t3->millisecond / 1000;
        t3->millisecond %= 1000;
    }
    if (t3->second >= 60) {
        t3->minute += t3->second / 60;
        t3->second %= 60;
    }
    if (t3->minute >= 60) {
        t3->hour += t3->minute / 60;
        t3->minute %= 60;
    }
}

// main 함수에서 호출
int main() {
    MyTime t1 = {1, 59, 58, 900};
    MyTime t2 = {0, 0, 2, 300};
    MyTime sum;

    addTime(t1, t2, &sum); // sum의 주소를 넘김

    printf("Result: %02d:%02d:%02d.%03d\n",
           sum.hour, sum.minute, sum.second, sum.millisecond);

    return 0;
}
