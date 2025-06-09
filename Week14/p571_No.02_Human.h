#pragma once
#include "p571_No.02_Monster.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char getche() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

class Human : public Monster {
public:
    Human(string n = "사람", string i = "ㅎ", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}

    ~Human() { cout << " [Human   ]"; }

    int getDirKey() {
        return getche();  // 단일 키 입력
    }

    void move(int** map, int maxx, int maxy) {
        if (kbhit()) {
            char ch = getDirKey();
            if (ch == 'a') p[0]--;
            else if (ch == 'd') p[0]++;
            else if (ch == 'w') p[1]--;
            else if (ch == 's') p[1]++;
            else return;

            clip(maxx, maxy);
            eat(map);
        }
    }
};
