#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "p348_No.03_canvas.h"

#define DIM 40

class Monster {
    std::string name, icon;
    int x, y, nItem, nEnergy; // nEnergy 속성
    static int count; // 정적 멤ber 변수: 몬스터 수

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
    void eat(int map[DIM][DIM]) {
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
            nEnergy += 10; // 아이템 먹으면 에너지 10 증가
            if (nEnergy > 200) nEnergy = 200; // 상한 200
        } else {
            nEnergy = std::max(0, nEnergy - 1); // 먹지 못하면 에너지 1 감소, 최소 0
        }
    }
public:
    Monster(std::string n = "몬스터", std::string i = "怪", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) { count++; } // count 증가
    ~Monster() { 
        std::cout << "\t" << name << icon << " 소멸합니다~~~\n"; 
        count--; // count 감소
    }

    Monster(const Monster& other)
        : name(other.name), icon(other.icon), x(other.x), y(other.y), 
          nItem(other.nItem), nEnergy(other.nEnergy) { count++; } // count 증가
    Monster& operator=(const Monster& other) {
        if (this != &other) {
            name = other.name;
            icon = other.icon;
            x = other.x;
            y = other.y;
            nItem = other.nItem;
            nEnergy = other.nEnergy;
        }
        return *this;
    }
    Monster(Monster&& other) noexcept
        : name(std::move(other.name)), icon(std::move(other.icon)),
          x(other.x), y(other.y), nItem(other.nItem), nEnergy(other.nEnergy) {
        other.x = 0;
        other.y = 0;
        other.nItem = 0;
        other.nEnergy = 0;
        count++; // count 증가
    }
    Monster& operator=(Monster&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            icon = std::move(other.icon);
            x = other.x;
            y = other.y;
            nItem = other.nItem;
            nEnergy = other.nEnergy;
            other.x = 0;
            other.y = 0;
            other.nItem = 0;
            other.nEnergy = 0;
        }
        return *this;
    }

    void draw(Canvas& canvas) { canvas.draw(x, y, icon); }
    void move(int map[DIM][DIM], int maxx, int maxy) {
        switch (std::rand() % 8) {
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
    void print() { 
        std::cout << icon << "(" << name << ", I:" << nItem << ", E:" << nEnergy << ") "; // 간결한 출력 형식
    }
    int getEnergy() const { return nEnergy; }
    std::string getIcon() const { return icon; }
    // 정적 멤버 함수: 현재 몬스터 수 출력
    static void printCount() {
        std::cerr << "현재 몬스터 수: " << count << std::endl;
    }
};

// 정적 멤버 변수 정의
int Monster::count = 0;