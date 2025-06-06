#pragma once
#include "p488_No.01_Canvas.h"
#define DIM 40

class Monster {
protected:
    string name, icon;    
    int x, y, nItem;        

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
    void eat(int** map) {
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
        }
    }
public:
    Monster(string n = "무명괴물", string i = "U", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0) {}
    virtual ~Monster() { cout << "\t" << name << icon << "사라집니다~~~\n"; }

    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
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
        clip(maxx, maxy);
        eat(map);
    }
    void print() { cout << "\t" << name << icon << ":" << nItem << endl; }
    string getName() { return name; } // 이름 반환
    int getNItem() { return nItem; } // 아이템 수 반환
};
