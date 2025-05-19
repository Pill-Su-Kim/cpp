#pragma once
#include <iostream>
#include <unistd.h>
#include "p446_No.02_Canvas.h"
#include "p446_No.02_monster.h"

#define DIM 40
#define MAXMONS 10 // 몬스터 수 증가

class MonsterWorld {
    int map[DIM][DIM];
    int xMax, yMax, nMon, nMove;
    Monster* mon[MAXMONS]; // 다형성을 위해 포인터 배열 사용
    Canvas canvas;

    int& Map(int x, int y) { return map[y][x]; }
    bool isDone() { return countItems() == 0; }
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }
    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "●");
        for (int i = 0; i < nMon; i++)
            mon[i]->draw(canvas);
        canvas.print("[ Monster World (몬스터월드) ]");

        std::cerr << " 전체 이동 횟수 = " << nMove << std::endl;
        std::cerr << " 남은 아이템 수 = " << countItems() << std::endl;
        for (int i = 0; i < nMon; i++)
            mon[i]->print();
        Monster::printCount();
    }
    void checkStarvation() {
        for (int i = 0; i < nMon; ) {
            if (mon[i]->getEnergy() == 0) {
                std::cerr << "몬스터 " << mon[i]->getIcon() << "가 에너지 부족으로 사라집니다!\n";
                delete mon[i];
                for (int j = i; j < nMon - 1; j++) {
                    mon[j] = mon[j + 1];
                }
                nMon--;
            } else {
                i++;
            }
        }
    }
public:
    MonsterWorld(int w, int h) : canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
        for (int i = 0; i < MAXMONS; i++) mon[i] = nullptr;
    }
    ~MonsterWorld() {
        for (int i = 0; i < nMon; i++) delete mon[i];
    }
    void add(const Monster& m) {
        if (nMon < MAXMONS) mon[nMon++] = m.clone(); // 복제본 저장
    }
    void play(int maxwalk, int wait) {
        print();
        std::cerr << " 몬스터를 시작합니다...";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++)
                mon[k]->move(map, xMax, yMax);
            nMove++;
            checkStarvation();
            print();
            if (isDone() || nMon == 0) break;
            usleep(wait * 1000);
        }
    }
};