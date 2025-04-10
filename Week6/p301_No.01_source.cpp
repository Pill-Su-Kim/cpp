// main.cpp
#include <iostream>
#include "p301_No_01_header.h"

using namespace std;

int main() {
    MyTime t1, t2, t3;

    t1.convert(3666);  // 1시간 1분 1초 -> 3666초를 시간, 분 ,초로 변환
    t2.convert(3599);  // 59분 59초 -> 3599초를 시간, 분 ,초로 변환

    cout << "t1: ";
    t1.print();
    
    cout << "t2: ";
    t2.print();

    t3 = t1.add(t2);  // t1 + t2

    cout << "t1 + t2 결과 (t3): ";
    t3.print();

    t3.reset();
    cout << "t3 리셋 후: ";
    t3.print();

    return 0;
}
