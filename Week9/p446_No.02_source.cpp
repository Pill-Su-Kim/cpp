#include <iostream>
#include <ctime>
#include <locale>
#include "p446_No.02_monsterworld.h"

int main() {
    // UTF-8 인코딩 설정
    std::locale::global(std::locale("ko_KR.UTF-8"));
    std::cout.imbue(std::locale());
    std::cerr.imbue(std::locale());

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int w = 16, h = 8;

    MonsterWorld game(w, h);
    game.add(Monster("고질라", "@", rand() % w, rand() % h));
    game.add(Monster("드래곤", "#", rand() % w, rand() % h));
    game.add(Smombi("스몸비1", "S", rand() % w, rand() % h));
    game.add(Jinagshi("강시1", "J", rand() % w, rand() % h));
    game.add(Siangshi("수퍼강시1", "SJ", rand() % w, rand() % h));
    game.add(CustomMonster("커스텀1", "C", rand() % w, rand() % h));
    game.play(500, 10);
    std::cout << "------게임 종료-------------------\n";
    return 0;
}