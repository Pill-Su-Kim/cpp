#pragma once
#include "p571_No.02_canvas.h"
#include "p571_No.02_VariousMonster.h"
#include "p571_No.02_Human.h"
#include "p571_No.02_Matrix.h"
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
        canvas.print("[ Monsterworld (Competitive) ]");

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
        cerr << " Press Enter to start (Arrow keys for '우', WASD for '좌')!!!!!";
        getchar(); // 사용자 입력 대기 (Enter)
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // 정규 입력 처리 및 에코 비활성화
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // 논블로킹 입력 설정

        for (int i = 0; i < maxwalk; i++) {
            // 입력 버퍼 비우기 로직 제거됨

            // 일반 몬스터 이동
            for (int k = 0; k < nMon; k++) {
                Tuman* tuman = dynamic_cast<Tuman*>(pMon[k]);
                if (!tuman) { // Tuman이 아닌 경우 (일반 몬스터)
                    pMon[k]->move(world.Data(), xMax, yMax);
                }
            }
            // Tuman 플레이어 이동,  getDirKey()로 입력 키를 받아 사람이 조작하는 객체만 수동 이동.
            for (int k = 0; k < nMon; k++) {
                Tuman* tuman = dynamic_cast<Tuman*>(pMon[k]);
                if (tuman) { // Tuman인 경우
                    int key = tuman->getDirKey(); //
                    if (key != 0) { // 유효한 키 입력이 있는 경우
                        tuman->moveHuman(key, world.Data(), xMax, yMax); //
                    }
                }
            }
            nMove++;
            print();
            if (isDone()) break;
            usleep(wait); // 지정된 시간만큼 대기
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 원래 터미널 설정 복원
        fcntl(STDIN_FILENO, F_SETFL, 0); // 원래 파일 상태 플래그 복원
        // 승자 표시
        int rightScore = 0, leftScore = 0;
        for (int i = 0; i < nMon; i++) {
            Tuman* tuman = dynamic_cast<Tuman*>(pMon[i]);
            if (tuman && tuman->getName() == "우") rightScore = tuman->getNItem();
            if (tuman && tuman->getName() == "좌") leftScore = tuman->getNItem();
        }
        cerr << "우 Score: " << rightScore << ", 좌 Score: " << leftScore << endl;
        if (rightScore > leftScore) cerr << "Winner: 우" << endl;
        else if (leftScore > rightScore) cerr << "Winner: 좌" << endl;
        else cerr << "Draw!" << endl;
    }
};