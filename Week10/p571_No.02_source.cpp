#include "p488_No.01_MonsterWorld_real.h"
#include "p488_No.01_VariousMonster.h"
#include "p488_No.01_Human_real.h"
#include <time.h>

int main() {
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Zombie("허접좀비", "&", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어", "@", rand() % w, rand() % h));
    game.add(new KGhost("처녀귀신", "#", rand() % w, rand() % h));
    game.add(new Jiangshi("대륙강시", "$", rand() % w, rand() % h, true));
    game.add(new Jiangshi("대륙강시2", "$2", rand() % w, rand() % h, false));
    game.add(new Tuman("우", "R", rand() % w, rand() % h)); // playerType 기본값 "Right" (화살표 키)
    game.add(new Tuman("좌", "L", rand() % w, rand() % h, "Left")); // playerType "Left" (WASD 키)로 수정
    game.play(500, 300000); // wait=300ms (0.3초)
    printf("-----Game Over-------------------\n");
}