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

    // 인덱스 연산자 오버로딩: 항목을 참조자로 반환
    int& operator[](int index) {
        if (index < 0 || index >= 100) {
            std::cerr << "Index out of bounds!" << std::endl;
            exit(EXIT_FAILURE);
        }
        return list[index];
    }
};


int main() {
    SampleList sl;

    std::cout << "Original value at index 5: " << sl[5] << std::endl;

    sl[5] = 999;  // 참조자로 반환되므로 직접 수정 가능

    std::cout << "Modified value at index 5: " << sl[5] << std::endl;

    return 0;
}