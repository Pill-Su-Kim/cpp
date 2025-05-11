#include "p348_No.02.h" // MyTime 클래스 헤더 파일 포함

int main() {
    double inputDuration;

    std::cout << "시간을 소수로 입력하세요 (예: 1.5 = 1시간 30분): ";
    std::cin >> inputDuration;

    MyTime timeObj(inputDuration); // 입력된 시간을 기반으로 객체 생성

    std::cout << "변환된 시간:" << std::endl;
    timeObj.print(); // 시간 출력

    return 0;
}
