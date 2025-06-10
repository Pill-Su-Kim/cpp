#pragma once
#include "p571_No.02_Monster.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

// Non-blocking, non-echoing getch() for Linux/macOS
inline int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Control schemes for players
enum ControlType { WASD, IJKL };

class Human : public Monster {
    ControlType controls;
public:
    Human(string n = "사람", string i = "웃", int px = 0, int py = 0, ControlType ct = WASD)
        : Monster(n, i, px, py), controls(ct) {}

    ~Human() { cout << " [Human   ]"; }

    // Human의 움직임은 키보드 입력으로만 제어되므로, 자동 'move'는 비워둡니다.
    void move(int** map, int maxx, int maxy) override { }

    // processInput 대신 이 함수를 사용합니다. Monster의 가상 함수를 재정의합니다.
    void handleInput(char key, int** map, int maxx, int maxy) override {
        bool moved = false;
        if (controls == WASD) {
            if (key == 'a' || key == 'A') { x--; moved = true; }
            else if (key == 'd' || key == 'D') { x++; moved = true; }
            else if (key == 'w' || key == 'W') { y--; moved = true; }
            else if (key == 's' || key == 'S') { y++; moved = true; }
        } else if (controls == IJKL) {
            if (key == 'j' || key == 'J') { x--; moved = true; }
            else if (key == 'l' || key == 'L') { x++; moved = true; }
            else if (key == 'i' || key == 'I') { y--; moved = true; }
            else if (key == 'k' || key == 'K') { y++; moved = true; }
        }

        if (moved) {
            totalMove++;
            clip(maxx, maxy);
            eat(map);
        }
    }
};