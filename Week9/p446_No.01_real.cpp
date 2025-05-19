#include <iostream>

class Point {
protected:
    int x, y;
public:
    Point(int xx, int yy) : x(xx), y(yy) { }

    virtual void draw() {
        std::cout << x << "," << y << " Draw point in ~\n";
    }
};

class Rectangle : public Point {
private:
    int width, height;

public:
    Rectangle(int xx, int yy, int w, int h)
        : Point(xx, yy), width(w), height(h) { }

    void draw() override {
        std::cout << "Draw rectangle at (" << x << "," << y 
                  << ") with width " << width 
                  << " and height " << height << std::endl;
    }
};

int main() {
    int xx, yy, w, h;

    // 사용자에게 입력 받기
    std::cout << "x 좌표 입력: ";
    std::cin >> xx;

    std::cout << "y 좌표 입력: ";
    std::cin >> yy;

    std::cout << "가로 길이(width) 입력: ";
    std::cin >> w;

    std::cout << "세로 길이(height) 입력: ";
    std::cin >> h;

    // Rectangle 객체 생성
    Rectangle rect(xx, yy, w, h);
    rect.draw();

    return 0;
}
