#pragma once
#include "p571_No.02_canvas.h"
#include "p571_No.02_VariousMonster.h"
#include "p571_No.02_Human.h"
#include "p571_No.02_Matrix.h"
#include <unistd.h>
#include <fcntl.h>
#define MAXMONS 10

class MonsterWorld {
    Matrix world;
    int xMax, yMax, nMon, nMove;
    Monster* pMon[MAXMONS];
    Canvas canvas;

    int& Map(int x, int y) { return world.elem(x, y); }
    bool isDone() { return countItems() == 0; }
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }
    void print() {
        canvas.clear(". "); 
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "O ");
        
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
        canvas.print("[ Monsterworld (Competitive) ]");

        cerr << " 전체이동횟수 = " << nMove << endl;
        cerr << " 남은 아이템수 = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
            pMon[i]->print();
    }
public:
    MonsterWorld(int w, int h) : world(h,w), canvas(w*2, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1; 
    }
    ~MonsterWorld() { 
        for (int i = 0; i < nMon; i++)
            delete pMon[i];
    }
    void add(Monster* m) {
        if (nMon < MAXMONS)
            pMon[nMon++] = m;
    }
    void play(int maxwalk, int wait) {
        print();
        cerr << " Press Enter to start (좌: WASD, 우: IJKL)!!!!!";
        getchar(); 

        struct termios oldt, newt;
        int oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        for (nMove = 0; nMove < maxwalk; nMove++) {
            char key = getchar(); 

            for (int k = 0; k < nMon; k++) {
                Human* human = dynamic_cast<Human*>(pMon[k]);
                if (human) {
                    // Human 객체일 경우, 키 입력이 있었으면 입력을 처리
                    if (key != EOF) {
                        human->handleInput(key, world.Data(), xMax, yMax);
                    }
                } else {
                    // 일반 몬스터일 경우, 스스로 움직임
                    pMon[k]->move(world.Data(), xMax, yMax);
                }
            }
            
            print();
            if (isDone()) {
                cerr << "모든 아이템을 획득했습니다!" << endl;
                break;
            }
            usleep(wait * 1000); 
        }
        
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        
        int leftScore = 0, rightScore = 0;
        for (int i = 0; i < nMon; i++) {
            if (pMon[i]->getName() == "좌") leftScore = pMon[i]->getNItem();
            if (pMon[i]->getName() == "우") rightScore = pMon[i]->getNItem();
        }
        cerr << "\n---------- Game Over ----------\n";
        cerr << "우 Score: " << rightScore << ", 좌 Score: " << leftScore << endl;
        if (rightScore > leftScore) cerr << "Winner: 우" << endl;
        else if (leftScore > rightScore) cerr << "Winner: 좌" << endl;
        else cerr << "Draw!" << endl;
    }
};