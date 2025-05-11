#include <iostream>
#include <cstring> // strlen, strcpy 사용
using namespace std;

class Sample {
    char* name;
    static int count;  //클래스의 모든 객체들이 공유하는 변수, count는 클래스 내의 객체 개수를 세는 변수


public:
    // 매개변수 생성자
    Sample(const char* nameInput) {
        this->name = new char[strlen(nameInput) + 1];  // 동적 메모리 할당, //동적 메모리 할당을 통해 name이라는 멤버 변수에 sample이라는 문자열을 저장할 공간을 만들어 주는 것
        strcpy(this->name, nameInput);  // 문자열 복사
        count++;  // 객체 생성 시 객체 수 증가
    }

    // 복사 생성자
    Sample(const Sample& other) {   // 얕은 복사 문제를 해결하기 위해 복사 생성자 안에 참조형 추가
        this->name = new char[strlen(other.name) + 1];  // 다른 객체의 name 길이에 맞게 메모리 할당
        strcpy(this->name, other.name);  // 기존 객체의 name을 복사
        count++;  // 객체 수 증가
    }

    // 소멸자
    ~Sample() {
        delete[] name;  // 동적 메모리 해제
        count--;  // 객체 소멸 시 객체 수 감소
    }

    // 정적 함수: 객체 개수 출력
    static void printCount() {
        cout << "현재 Sample 객체 수: " << count << endl;
    }
};

// 정적 변수 초기화
int Sample::count = 0;

int main() {
    Sample::printCount();  // 현재 객체 수: 0

    Sample a("sample");  //자료형char의 형태의 매개변수를 받는꼴인 형태,//sample이라는 내가 원하는 형태의 메모리를 할당 하기위해 동적메모리 할당을 한것
    Sample::printCount();  // 현재 객체 수: 1

    // 복사 생성자 호출
    Sample b(a);  // a를 복사하여 b 객체 생성
    Sample::printCount();  // 현재 객체 수: 2

    return 0;
}
