#include <iostream>
#include <stdexcept>

class TimeHMS {
    int hour, min, sec;

    // 시간 정규화
    void normalize() {
        if (sec >= 60 || sec < 0) {
            min += sec / 60;
            sec %= 60;
            if (sec < 0) {
                sec += 60;
                min--;
            }
        }
        if (min >= 60 || min < 0) {
            hour += min / 60;
            min %= 60;
            if (min < 0) {
                min += 60;
                hour--;
            }
        }
    }

public:
    TimeHMS(int h = 0, int m = 0, int s = 0) : hour(h), min(m), sec(s) {
        normalize();
    }

    // 1. + 연산자 중복
    TimeHMS operator+(const TimeHMS& other) const {
        TimeHMS result(hour + other.hour, min + other.min, sec + other.sec);
        result.normalize();
        return result;
    }

    // 2. - 연산자 중복
    TimeHMS operator-(const TimeHMS& other) const {
        TimeHMS result(hour - other.hour, min - other.min, sec - other.sec);
        result.normalize();
        return result;
    }

    // 3. ==, != 연산자 중복
    bool operator==(const TimeHMS& other) const {
        return hour == other.hour && min == other.min && sec == other.sec;
    }
    bool operator!=(const TimeHMS& other) const {
        return !(*this == other);
    }

    // 4. 전위 증감 연산자 (시간 단위 증가/감소)
    TimeHMS& operator++() {
        hour++;
        return *this;
    }
    TimeHMS& operator--() {
        hour--;
        return *this;
    }

    // 5. 후위 증감 연산자 (초 단위 증가/감소)
    TimeHMS operator++(int) {
        TimeHMS temp = *this;
        sec++;
        normalize();
        return temp;
    }
    TimeHMS operator--(int) {
        TimeHMS temp = *this;
        sec--;
        normalize();
        return temp;
    }

    // 6. 인덱스 연산자 중복: 0=시, 1=분, 2=초
    int operator[](int index) const {
        switch (index) {
            case 0: return hour;
            case 1: return min;
            case 2: return sec;
            default: throw std::out_of_range("Index must be 0(hour), 1(min), or 2(sec)");
        }
    }

    // 7. int 형 변환 연산자: 초 단위 전체 시간
    operator int() const {
        return hour * 3600 + min * 60 + sec;
    }

    // 8. double 형 변환 연산자: 시간 단위 전체 시간
    operator double() const {
        return hour + min / 60.0 + sec / 3600.0;
    }

    // 9. 정수 * TimeHMS (friend 함수)
    friend TimeHMS operator*(int n, const TimeHMS& t) {
        int total_sec = (int)t * n;
        return TimeHMS(0, 0, total_sec);
    }

    // 디버그용 출력
    void print() const {
        std::cout << hour << "시간 " << min << "분 " << sec << "초\n";
    }
};


int main() {
    TimeHMS t1(1, 20, 30), t2(2, 50, 45), t3;

    t3 = t1 + t2;
    t3.print();  // 4시간 11분 15초

    t3 = t2 - t1;
    t3.print();  // 1시간 30분 15초

    std::cout << (t1 == t2) << "\n"; // 0
    std::cout << (t1 != t2) << "\n"; // 1

    ++t1;
    t1.print(); // 2시간 20분 30초

    --t1;
    t1.print(); // 1시간 20분 30초

    t1++;
    t1.print(); // 1시간 20분 31초

    t1--;
    t1.print(); // 1시간 20분 30초

    std::cout << "시: " << t1[0] << ", 분: " << t1[1] << ", 초: " << t1[2] << "\n";

    int seconds = (int)t1;
    std::cout << "초 단위: " << seconds << "\n"; // 4830초

    double hours = (double)t1;
    std::cout << "시간 단위: " << hours << "\n"; // 약 1.3417시간

    t3 = 2 * t1;
    t3.print(); // 2시간 41분 0초 (4830 * 2 = 9660초 → 2시간 41분 0초)

    return 0;
}
