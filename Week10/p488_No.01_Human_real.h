#pragma once
#include "p488_No.01_Monter.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
                                  //방향을 상수로 정의하여 키 값에 의미를 부여.
enum Direction { Left = 75, Right = 77, Up = 72, Down = 80, W = 'w', A = 'a', S = 's', D = 'd' };

class Human : public Monster {
protected:                            //kbhit() 함수는 키보드로부터 입력이 들어왔는지 여부를 확인하는 함수
    virtual int getDirKey() {             //15행부터 22행까지 코드가 khbit()을 대체하기 위해 작성된 코드, 이를 비차단 방식으로 체크
        struct termios oldt, newt;           //getchar()가 입력이 없을 때 멈추지 않도록 설정
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
                switch (ch) {   //방향키에 해당
                    case 'D': return Left;
                    case 'C': return Right;
                    case 'A': return Up;
                    case 'B': return Down;
                }
            }   //그 외에 W,S,A,D키 이다
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
               //현재 방향 입력을 받아서 위치 x, y를 수정.
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
            //이 함수는 가상함수 Human::getDirKey()를 오버라이드해서, 특정 입력 방식만을 인식하도록 제한, 즉 wsad 혹은 방향키중 하나의 정해진 키만 입력 받도록함
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
                        case 'D': return Left;      //리눅스 터미널에서 방향키 입력을 처리하는 코드
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
