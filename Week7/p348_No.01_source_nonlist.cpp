// main.cpp
#include <iostream>
#include "p348_No.01_nonlist.h"

using namespace std;

int main() {
    MyTime t1, t2, t3;  // 기본 생성자 호출 (0으로 초기화됨)

    t1.convert(3666);  // 1시간 1분 1초 (3666초)
    t2.convert(3599);  // 59분 59초 (3599초)

    cout << "t1: ";
    t1.print();  // t1의 시간을 출력
    
    cout << "t2: ";
    t2.print();  // t2의 시간을 출력

    t3 = t1.add(t2);  // t1 + t2

    cout << "t1 + t2 결과 (t3): ";
    t3.print();  // t1과 t2를 더한 시간 출력

    t3.reset();  // t3 리셋
    cout << "t3 리셋 후: ";
    t3.print();  // 리셋 후 출력

    return 0;
}

