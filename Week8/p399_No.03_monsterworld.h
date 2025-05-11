#pragma once
#include <iostream>
#include <unistd.h>
#include "p348_No.03_canvas.h"
#include "p399_No.03.monster.h"

#define DIM 40
#define MAXMONS 5

class MonsterWorld {
    int map[DIM][DIM];
    int xMax, yMax, nMon, nMove;
    Monster mon[MAXMONS];
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
            mon[i].draw(canvas);
        canvas.print("[ Monster World (몬스터월드) ]");

        std::cerr << " 전체 이동 횟수 = " << nMove << std::endl;
        std::cerr << " 남은 아이템 수 = " << countItems() << std::endl;
        for (int i = 0; i < nMon; i++)
            mon[i].print();
        Monster::printCount(); // 화면 갱신 시 몬스터 수 출력
    }
    void checkStarvation() {
        for (int i = 0; i < nMon; ) {
            if (mon[i].getEnergy() == 0) {
                std::cerr << "몬스터 " << mon[i].getIcon() << "가 에너지 부족으로 사라집니다!\n";
                // 뒤의 몬스터를 앞으로 이동시켜 제거
                for (int j = i; j < nMon - 1; j++) {
                    mon[j] = std::move(mon[j + 1]);
                }
                nMon--; // 몬스터 수 감소
            } else {
                i++; // 에너지가 0이 아니면 다음 몬스터로
            }
        }
    }
public:
    MonsterWorld(int w, int h) : canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
    }
    ~MonsterWorld() {}
    void add(const Monster& m) {
        if (nMon < MAXMONS) mon[nMon++] = m;
    }
    void play(int maxwalk, int wait) {
        print();
        std::cerr << " 몬스터를 시작합니다...";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++)
                mon[k].move(map, xMax, yMax);
            nMove++;
            checkStarvation(); // 각 이동 후 에너지 확인 및 몬스터 제거
            print();
            if (isDone() || nMon == 0) break; // 아이템 없거나 몬스터 모두 사라지면 종료
            usleep(wait * 1000);
        }
    }
};