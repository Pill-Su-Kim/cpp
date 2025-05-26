#pragma once
#include "p488_No.01_Canvas.h"      
#include "p488_No.01_VariousMonster.h"
#include "p488_No.01_Matrix.h"
#include <unistd.h>
#define MAXMONS 8

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
        canvas.clear("O "); // 초기 맵을 'O'로 설정
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "O ");
                else canvas.draw(x, y, ". "); // 아이템이 없으면 '.'
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
        canvas.print("[ Monsterworld (Basic) ]");

        cerr << " 전체이동횟수 = " << nMove << endl;
        cerr << " 남은 아이템수 = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
            pMon[i]->print();
    }
public:
    MonsterWorld(int w, int h) : world(h,w), canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
        canvas.clear("O "); // 초기 맵을 'O'로 채움
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
        cerr << " Press the Enter!!!!!";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++)
                pMon[k]->move(world.Data(), xMax, yMax);
            nMove++;
            print();
            if (isDone()) break;
            usleep(wait);
        }
    }
};