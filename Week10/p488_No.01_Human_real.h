#pragma once
#include "p488_No.01_Monter.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80, W = 'w', A = 'a', S = 's', D = 'd' };

class Human : public Monster {
protected:
    virtual int getDirKey() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, 0);
        if (ch == 27) { // ANSI 이스케이프 시퀀스 시작
            usleep(1000); // 후속 문자 대기
            int ch2 = getchar();
            if (ch2 == 91) {
                ch = getchar();
                // cerr << "Arrow key input: " << ch << endl; // 디버깅 출력
                switch (ch) {
                    case 'D': return Left;
                    case 'C': return Right;
                    case 'A': return Up;
                    case 'B': return Down;
                }
            }
        } else if (ch == W || ch == A || ch == S || ch == D) {
            // cerr << "WASD input: " << (char)ch << endl; // 디버깅 출력
            return ch;
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
        else if (ch == W) y--;
        else if (ch == A) x--;
        else if (ch == S) y++;
        else if (ch == D) x++;
        else return;
        clip(maxx, maxy);
        eat(map);
    }
};

class Tuman : public Human {
    string playerType; // "Right" for 우 (arrow keys), "Left" for 좌 (WASD)
public:
    Tuman(string n = "미래인류", string i = "H", int px = 0, int py = 0, string type = "Right")
        : Human(n, i, px, py), playerType(type) {}
    ~Tuman() { cout << " [Tuman   ]"; }

    int getDirKey() override {
        int ch = getchar();
        if (ch != -1) {
            // cerr << "Player: " << playerType << ", Raw input: " << ch << endl; // 디버깅 출력
            if (playerType == "Right" && ch == 27) { // 화살표 키 (우)
                usleep(1000); // 후속 문자 대기
                int ch2 = getchar();
                if (ch2 == 91) {
                    ch = getchar();
                    // cerr << "Arrow key code: " << ch << endl; // 디버깅 출력
                    switch (ch) {
                        case 'D': return Left;
                        case 'C': return Right;
                        case 'A': return Up;
                        case 'B': return Down;
                    }
                }
            } else if (playerType == "Left" && (ch == W || ch == A || ch == S || ch == D)) {
                return ch;
            }
        }
        return 0;
    }

    void moveHuman(int ch, int** map, int maxx, int maxy) {
        if (playerType == "Right") { // 화살표 키만 처리
            if (ch == Left) x--;
            else if (ch == Right) x++;
            else if (ch == Up) y--;
            else if (ch == Down) y++;
            else return;
        } else if (playerType == "Left") { // WASD만 처리
            if (ch == W) y--;
            else if (ch == A) x--;
            else if (ch == S) y++;
            else if (ch == D) x++;
            else return;
        } else {
            return;
        }
        clip(maxx, maxy);
        eat(map);
    }
};
