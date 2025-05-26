#include "p488_No.01_MonsterWorld_prototype.h"
#include "p488_No.01_VariousMonster.h"
#include "p488_No.01_Human_real.h"
#include <time.h>

int main()
{
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;
	MonsterWorld game(w, h);

	game.add(new Zombie("허접좀비", "&", rand() % w, rand() % h));
	game.add(new Vampire("뱀파이어", "@", rand() % w, rand() % h));
	game.add(new KGhost("처녀귀신", "#", rand() % w, rand() % h));
	game.add(new Jiangshi("대륙강시", "$", rand() % w, rand() % h, true));
	game.add(new Jiangshi("대륙강시2", "$2", rand() % w, rand() % h, false));
    game.add(new Human("미래인류", "%", rand() % w, rand() % h));
	game.play(500, 100000);
	printf("-----Game Over-------------------\n");
}