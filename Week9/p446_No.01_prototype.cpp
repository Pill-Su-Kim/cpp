#include<iostream>

class Point{
    protected:
        int x, y;
    public:
        Point(int xx, int yy) : x(xx), y(yy){ }
        void draw(){
            std::cout << x << "," << y << "Draw point in ~\n";

        }
};