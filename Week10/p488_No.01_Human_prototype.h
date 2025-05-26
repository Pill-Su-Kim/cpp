#pragma once
#include "p488_No.01_Monter.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };

class Human : public Monster {
private:
    int getDirKey() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // 비차단, 에코 비활성화
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // 비차단 입력 설정
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, 0); // 원래 상태로 복구
        if (ch == 27 && getchar() == 91) { // ANSI 이스케이프 시퀀스 (화살표 키)
            ch = getchar();
            switch (ch) {
                case 'D': return Left;  // 왼쪽 화살표
                case 'C': return Right; // 오른쪽 화살표
                case 'A': return Up;    // 위쪽 화살표
                case 'B': return Down;  // 아래쪽 화살표
            }
        }
        return 0;
    }

public:
    Human(string n = "미래인류", string i = "H", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    ~Human() { cout << " [Human   ]"; }

    void move(int** map, int maxx, int maxy) {
        int ch = getDirKey();
        if (ch == Left) x--;
        else if (ch == Right) x++;
        else if (ch == Up) y--;
        else if (ch == Down) y++;
        else return;
        clip(maxx, maxy);
        eat(map);
    }
};
