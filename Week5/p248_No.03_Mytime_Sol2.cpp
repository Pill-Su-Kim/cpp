#include <iostream>
#include "p248_No.03_Mytime_header_Sol2.h"
using namespace std;

// 함수 정의
void addTime(MyTime t1, MyTime t2, MyTime& t3) {
    t3.millisecond = t1.millisecond + t2.millisecond;
    t3.second = t1.second + t2.second;
    t3.minute = t1.minute + t2.minute;
    t3.hour = t1.hour + t2.hour;

    if (t3.millisecond >= 1000) {
        t3.second += t3.millisecond / 1000;
        t3.millisecond %= 1000;
    }
    if (t3.second >= 60) {
        t3.minute += t3.second / 60;
        t3.second %= 60;
    }
    if (t3.minute >= 60) {
        t3.hour += t3.minute / 60;
        t3.minute %= 60;
    }
}

// main 함수
int main() {
    MyTime t1 = {1, 59, 58, 900};
    MyTime t2 = {0, 0, 2, 300};
    MyTime t3; // 결과를 저장할 구조체

    addTime(t1, t2, t3);  // 결과가 t3에 저장됨

    cout << "Result: "
         << t3.hour << "시간 "
         << t3.minute << "분 "
         << t3.second << "초 "
         << t3.millisecond << "밀리초" << endl;

    return 0;
}
