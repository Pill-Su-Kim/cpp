#include <iostream>
#include <ctime>
#include "p348_No.03_monsterworld.h"

int main() {
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