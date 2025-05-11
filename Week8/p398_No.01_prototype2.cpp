#include <iostream>
#include <cstring>
using namespace std;

class Sample {
    char* name;
    static int count; // 정적 변수 선언  //클래스의 모든 객체들이 공유하는 변수, count는 클래스 내의 객체 개수를 세는 변수

public:
    // 기본 생성자
    Sample() {
        name = nullptr;
        count++;
    }

    // 매개변수 생성자, 동적 메모리 할당 부분
    Sample(const char* nameInput) {   //동적 메모리 할당을 통해 name이라는 멤버 변수에 sample이라는 문자열을 저장할 공간을 만들어 주는 것
        name = new char[strlen(nameInput) + 1];
        strcpy(name, nameInput);
        count++;
    }

    // 복사 생성자, 동적 메모리 할당 부분
    Sample(const Sample& other) { // 얕은 복사 문제를 해결하기 위해 복사 생성자 안에 참조형 추가
        if (other.name) {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        } else {
            name = nullptr;
        }
        count++;
    }

    // 소멸자
    ~Sample() {
        delete[] name;
        count--;
    }

    // 정적 함수: 객체 수 출력
    static void printCount() {
        cout << "현재 Sample 객체 수: " << count << endl;
    }
};

// 정적 멤버 변수 정의 (클래스 외부에서 초기화 필요)
int Sample::count = 0; 

// main 함수
int main() {
    Sample::printCount();  // 현재 객체 수 출력 (0)
    
    Sample a("sample");  //자료형char의 형태의 매개변수를 받는꼴인 형태,//sample이라는 내가 원하는 형태의 메모리를 할당 하기위해 동적메모리 할당을 한것
    Sample::printCount();  // 1

    Sample b(a);
    Sample::printCount();  // 2

    return 0; // main은 int형이어야 함
}
