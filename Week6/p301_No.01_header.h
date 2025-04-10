// MyTime.h
#ifndef MYTIME_H
#define MYTIME_H

#include <iostream>  // std::cout, std::endl 사용을 위해 필요
#include <iomanip> //selfill()을 사용하기 위한 헤더

class MyTime {
private:
    int hours;
    int minutes;
    int seconds;

public:
    // 초 단위로 시간 변환
    inline void convert(double duration) {
        int total_seconds = static_cast<int>(duration);
        hours = total_seconds / 3600;
        minutes = (total_seconds % 3600) / 60;
        seconds = total_seconds % 60;
    }

    // 시간 출력
    inline void print() {
        std::cout << hours << "시간 " << minutes << "분 " << seconds << "초" << std::endl;
        std::cout << std::setw(2) << std::setfill('0') << hours << ":"
              << std::setw(2) << std::setfill('0') << minutes << ":"  //자릿수를 0으로 채우기 위해 한 입출력 조작자 setfill()을 사용
              << std::setw(2) << std::setfill('0') << seconds << std::endl;
        
    }

    // 두 시간 더하기
    inline MyTime add(MyTime t) {
        MyTime result;
        int total_sec1 = hours * 3600 + minutes * 60 + seconds;
        int total_sec2 = t.hours * 3600 + t.minutes * 60 + t.seconds;
        result.convert(total_sec1 + total_sec2);
        return result;
    }

    // 시간 초기화
    inline void reset() {
        hours = minutes = seconds = 0;
    }
    
    inline void read() {
        std::cout << "시간(시간 분 초)을 입력하세요: ";
        std::cin >> hours >> minutes >> seconds; //사용자 입력 → cin이 받음 → 변수(hours, minutes, seconds)에 저장

    
        // 입력값 보정 (예: 70초 입력하면 1분 10초로 변환)
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
