// main.cpp
#include <iostream>
#include "p348_No.01_including_list.h"

using namespace std;
int main() {
    // 객체 생성 시, 생성자에 값 전달
    MyTime t1(1, 1, 1);  // 1시간 1분 1초로 초기화
    MyTime t2(0, 59, 59);  // 0시간 59분 59초로 초기화
    MyTime t3;  // 기본값 (0시간 0분 0초)으로 초기화

    // 객체의 값 출력
    cout << "t1: ";
    t1.print();
    
    cout << "t2: ";
    t2.print();

    // t1과 t2 더하기
    t3 = t1.add(t2);  // t1 + t2

    cout << "t1 + t2 결과 (t3): ";
    t3.print();

    // t3 리셋
    t3.reset();
    cout << "t3 리셋 후: ";
    t3.print();

    return 0;
}
