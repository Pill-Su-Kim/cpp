#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "p446_No.02_Canvas.h"

#define DIM 40

class Monster {
protected:
    std::string name, icon;
    int x, y, nItem, nEnergy;
    static int count;

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
            nEnergy += 10;
            if (nEnergy > 200) nEnergy = 200;
        } else {
            nEnergy = std::max(0, nEnergy - 1);
        }
    }
public:
    Monster(std::string n = "몬스터", std::string i = "#", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) { count++; }
    virtual ~Monster() { 
        std::cout << "\t" << name << icon << " 소멸합니다~~~\n"; 
        count--;
    }

    Monster(const Monster& other)
        : name(other.name), icon(other.icon), x(other.x), y(other.y), 
          nItem(other.nItem), nEnergy(other.nEnergy) { count++; }
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
        count++;
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

    virtual void draw(Canvas& canvas) { canvas.draw(x, y, icon); }
    virtual void move(int map[DIM][DIM], int maxx, int maxy) {
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
        std::cout << icon << "(" << name << ", I:" << nItem << ", E:" << nEnergy << ") ";
    }
    int getEnergy() const { return nEnergy; }
    std::string getIcon() const { return icon; }
    static void printCount() {
        std::cerr << "현재 몬스터 수: " << count << std::endl;
    }
    virtual Monster* clone() const {
        return new Monster(*this);
    }
};

class Smombi : public Monster {
public:
    Smombi(std::string n = "스몸비", std::string i = "S", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    void move(int map[DIM][DIM], int maxx, int maxy) override {
        switch (std::rand() % 4) {
        case 0: x++; y--; break;
        case 1: x++; y++; break;
        case 2: x--; y++; break;
        case 3: x--; y--; break;
        }
        clip(maxx, maxy);
        eat(map);
    }
    Monster* clone() const override {
        return new Smombi(*this);
    }
};

class Jinagshi : public Monster {
protected:
    bool isHorizontal;
    int direction;
public:
    Jinagshi(std::string n = "강시", std::string i = "J", int px = 0, int py = 0)
        : Monster(n, i, px, py), isHorizontal(std::rand() % 2), direction(std::rand() % 2 ? 1 : -1) {}
    void move(int map[DIM][DIM], int maxx, int maxy) override {
        int steps = std::rand() % 3 + 1;
        if (isHorizontal) {
            x += direction * steps;
        } else {
            y += direction * steps;
        }
        clip(maxx, maxy);
        eat(map);
        if (std::rand() % 2) direction = -direction;
    }
    Monster* clone() const override {
        return new Jinagshi(*this);
    }
};

class Siangshi : public Jinagshi {
    int moveCount;
public:
    Siangshi(std::string n = "수퍼강시", std::string i = "SJ", int px = 0, int py = 0)
        : Jinagshi(n, i, px, py), moveCount(0) {}
    void move(int map[DIM][DIM], int maxx, int maxy) override {
        Jinagshi::move(map, maxx, maxy);
        moveCount++;
        if (moveCount >= 10) {
            isHorizontal = !isHorizontal;
            moveCount = 0;
        }
    }
    Monster* clone() const override {
        return new Siangshi(*this);
    }
};

class CustomMonster : public Monster {
public:
    CustomMonster(std::string n = "커스텀몬스터", std::string i = "C", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    void move(int map[DIM][DIM], int maxx, int maxy) override {
        x += (std::rand() % 7 - 3);
        y += (std::rand() % 7 - 3);
        clip(maxx, maxy);
        eat(map);
    }
    Monster* clone() const override {
        return new CustomMonster(*this);
    }
};

int Monster::count = 0;