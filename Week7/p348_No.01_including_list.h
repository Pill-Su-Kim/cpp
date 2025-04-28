#ifndef MYTIME_H
#define MYTIME_H

#include <iostream>  
#include <iomanip>  

class MyTime {
private:
    int hours;
    int minutes;
    int seconds;

public:
    // 기본 생성자
    MyTime() : hours(0), minutes(0), seconds(0) {} //이건 기본생성자 -> 매개변수가 없을 경우에는 0시0분0초 로 초기화

    // 매개변수 있는 생성자
    MyTime(int h, int m, int s) : hours(h), minutes(m), seconds(s) {     //주어진 시간을 h, m, s로 초기화 하는 생성자
        // 입력값 보정 (초, 분이 60 이상인 경우)
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
    }

    // 초 단위로 시간 변환 멤버함수
    void convert(double duration) {
        int total_seconds = static_cast<int>(duration);
        hours = total_seconds / 3600;
        minutes = (total_seconds % 3600) / 60;
        seconds = total_seconds % 60;
    }

    // 시간 출력 멤버함수
    inline void print() {
        std::cout << hours << "시간 " << minutes << "분 " << seconds << "초" << std::endl;
        std::cout << std::setw(2) << std::setfill('0') << hours << ":"
                  << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << std::setfill('0') << seconds << std::endl;
    }

    // 두 시간 더하기 멤버함수
    inline MyTime add(MyTime t) {
        MyTime result;
        int total_sec1 = hours * 3600 + minutes * 60 + seconds;
        int total_sec2 = t.hours * 3600 + t.minutes * 60 + t.seconds;
        result.convert(total_sec1 + total_sec2);
        return result;
    }

    // 시간 초기화 멤버함수
    inline void reset() {
        hours = minutes = seconds = 0;
    }

    // 시간 입력 멤버함수
    inline void read() {
        std::cout << "시간(시간 분 초)을 입력하세요: ";
        std::cin >> hours >> minutes >> seconds;

        // 입력값 보정
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
    }
};

#endif // MYTIME_H
