#pragma once
#include "p571_No.02_canvas.h"
#include <string>
#include <iostream>
using namespace std;

class Monster {
protected:
    string name, icon;    
    int x, y, nItem;        
    double totalMove; 

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }

    void eat(int** map) {
        if (map[y][x] > 0) { 
            map[y][x] = 0;   
            nItem++;
        }
    }

public:
    Monster(string n = "무명괴물", string i = "U", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), totalMove(0) {}

    virtual ~Monster() {
        cout << "\t" << name << icon << " 사라집니다~~~\n";
    }

    void draw(Canvas& canvas) {
        canvas.draw(x, y, icon);
    }

    virtual void move(int** map, int maxx, int maxy) {
        switch (rand() % 8) {
            case 0: y--; break;
            case 1: x++; y--; break;
            case 2: x++; break;
            case 3: x++; y++; break;
            case 4: y++; break;
            case 5: x--; y++; break;
            case 6: x--; break;
            case 7: x--; y--; break;
        }
        totalMove++;
        clip(maxx, maxy);
        eat(map);
    }
    
    // 이 가상 함수를 추가합니다.
    // Human 객체는 이 함수를 재정의하여 키보드 입력을 처리합니다.
    // 일반 Monster 객체에게는 아무 동작도 하지 않습니다.
    virtual void handleInput(char key, int** map, int maxx, int maxy) { }

    void print() {
        cout << "\t" << name << icon << ": " << nItem << "개 (이동:" << totalMove << ")" << endl;
    }

    string getName() { return name; }
    int getNItem() { return nItem; }
    double getTotalMove() { return totalMove; }
};