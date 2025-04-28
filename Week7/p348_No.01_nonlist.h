// MyTime.h
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
    // 멤버 초기화 리스트 없이, 중괄호 { } 안에서 대입하는 생성자
    MyTime(int h = 0, int m = 0, int s = 0) {   // 만약 여기에 int h =0 같이 0으로 초기화를 안해두면 호출시 쓰레기 값이 나옴 -> 값이 무작위로 나옴
        hours = h;
        minutes = m;
        seconds = s;
    }

    void convert(double duration) {
        int total_seconds = static_cast<int>(duration);
        hours = total_seconds / 3600;
        minutes = (total_seconds % 3600) / 60;
        seconds = total_seconds % 60;
    }

    inline void print() {
        std::cout << hours << "시간 " << minutes << "분 " << seconds << "초" << std::endl;
        std::cout << std::setw(2) << std::setfill('0') << hours << ":"
                  << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << std::setfill('0') << seconds << std::endl;
    }

    inline MyTime add(MyTime t) {
        MyTime result;
        int total_sec1 = hours * 3600 + minutes * 60 + seconds;
        int total_sec2 = t.hours * 3600 + t.minutes * 60 + t.seconds;
        result.convert(total_sec1 + total_sec2);
        return result;
    }

    inline void reset() {
        hours = minutes = seconds = 0;
    }

    inline void read() {
        std::cout << "시간(시간 분 초)을 입력하세요: ";
        std::cin >> hours >> minutes >> seconds;

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
