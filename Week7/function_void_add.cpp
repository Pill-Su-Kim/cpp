#include <iostream>
#include <complex> // std::complex는 쓰지 않고 직접 정의할게
using namespace std;

// 직접 복소수 구조체 정의
class MyComplex {
public: 
    double real;
    double imag;

    // 3. 멤버함수 (void, 참조전달)
    void addByRef(const MyComplex& a, const MyComplex& b) {
        real = a.real + b.real;
        imag = a.imag + b.imag;
    }

    // 4. 멤버함수 (return 참조전달)
    MyComplex& addAndReturn(const MyComplex& a, const MyComplex& b) {
        real = a.real + b.real;
        imag = a.imag + b.imag;
        return *this;
    }

    // 5. 연산자 오버로딩
    MyComplex operator+(const MyComplex& other) const {
        MyComplex temp;
        temp.real = real + other.real;
        temp.imag = imag + other.imag;
        return temp;
    }

    // 출력 함수 (편의용)
    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

// 1. 일반함수 (참조전달)
void addComplexRef(const MyComplex& a, const MyComplex& b, MyComplex& c) {
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
}

// 2. 일반함수 (값전달)
MyComplex addComplexValue(MyComplex a, MyComplex b) {
    MyComplex c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}

int main() {
    MyComplex a = {1, 2}; // 1 + 2i
    MyComplex b = {3, 4}; // 3 + 4i
    MyComplex c;

    cout << "1. 일반함수 (참조전달): ";
    addComplexRef(a, b, c);
    c.print();

    cout << "2. 일반함수 (값전달): ";
    c = addComplexValue(a, b);
    c.print();

    cout << "3. 멤버함수 (void, 참조전달): ";
    c.addByRef(a, b);
    c.print();

    cout << "4. 멤버함수 (return 참조전달): ";
    c.addAndReturn(a, b);
    c.print();

    cout << "5. 연산자 오버로딩 (+): ";
    c = a + b;
    c.print();

    return 0;
}


