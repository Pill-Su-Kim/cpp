#include <iostream>
#include <ctime>
#include <locale>
#include "p399_No.03_monsterworld.h"

int main() {
    // UTF-8 인코딩 설정
    std::locale::global(std::locale("en_US.UTF-8")); // 또는 "ko_KR.UTF-8"
    std::cout.imbue(std::locale());
    std::cerr.imbue(std::locale());

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int w = 16, h = 8;

    MonsterWorld game(w, h);
    Monster m("고질라", "怪", rand() % w, rand() % h);
    game.add(m);
    game.add(Monster("드래곤", "龍", rand() % w, rand() % h));
    game.add(Monster("유니콘", "馬", rand() % w, rand() % h));
    game.add(Monster("켄타", "牛", rand() % w, rand() % h));
    game.play(500, 10);
    std::cout << "------게임 종료-------------------\n";
    return 0;
}