// main.cpp
#include <iostream>
#include "p301_No_01_header.h"

using namespace std;

int main() {
    MyTime t1, t2, t3; //MyTime 클래스 타입 객체 (object)들을 3개 만듬->t1, t2,t3 -> MyTime 클래스 생성자(MyTime()) 호출, 

    t1.convert(3666);  // 1시간 1분 1초 -> 3666초를 시간, 분 ,초로 변환
    t2.convert(3599);  // 59분 59초 -> 3599초를 시간, 분 ,초로 변환

    cout << "t1: ";//t1객체에 convert()함수 호출 -> 초를 받아서 시, 분, 초 로 변환
    t1.print();
    
    cout << "t2: ";//t1객체에 convert()함수 호출 -> 초를 받아서 시, 분, 초 로 변환
    t2.print();

    t3 = t1.add(t2);  // t1 + t2

    cout << "t1 + t2 결과 (t3): ";  // print()함수를 통해 시간, 분,초를 끼워서 출력
    t3.print(); //t1 + t2의 결과를 t3에 저장을 하였기 때문에  t3를 출력

    t3.reset();
    cout << "t3 리셋 후: ";
    t3.print();

    return 0;
}





