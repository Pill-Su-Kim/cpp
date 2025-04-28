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

public:   //예를 들어 1.5시간 이 입력될 시 3600초로 초기화
    MyTime(double duration) 
    : hours(static_cast<int>(duration * 3600) / 3600),        // 초를 시간으로 초기화
    minutes((static_cast<int>(duration * 3600) % 3600) / 60), // 남은 초를 분으로 초기화
    seconds(static_cast<int>(duration * 3600) % 60)          // 남은 초를 초로 초기화
{
// 생성자 본문에서는 아무 작업도 하지 않음
}

 

    // 시간을 출력하는 함수
    inline void print() {
        std::cout << hours << "시간 " << minutes << "분 " << seconds << "초" << std::endl;
        std::cout << std::setw(2) << std::setfill('0') << hours << ":"
                  << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << std::setfill('0') << seconds << std::endl;
    }
};

#endif // MYTIME_H
