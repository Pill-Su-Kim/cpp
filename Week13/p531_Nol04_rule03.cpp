#include <iostream>
#include <cstdlib>

class SampleList {
    int list[100];

public:
    SampleList() {
        for (int x = 0; x < 100; x++) {
            list[x] = rand() % 1000;
        }
    }

    // 함수 호출 연산자 중복: 두 수의 곱을 인덱스로 사용
    int& operator()(int a, int b) {
        int index = a * b;

        if (index < 0 || index >= 100) {
            std::cerr << "Index (" << index << ") out of bounds!" << std::endl;
            exit(EXIT_FAILURE);
        }

        return list[index];
    }
};


int main() {
    SampleList sl;

    int a = 2, b = 3;

    std::cout << "Value at index " << a*b << ": " << sl(a, b) << std::endl;

    sl(a, b) = 888;  // a*b 위치 값 수정

    std::cout << "Modified value at index " << a*b << ": " << sl(a, b) << std::endl;

    return 0;
}
