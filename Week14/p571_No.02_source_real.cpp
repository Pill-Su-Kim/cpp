#include "p571_No.02_MonsterWorld.h"
#include "p571_No.02_Human.h"
#include "RankingBoard.h"
#include <time.h>
#include <iostream>

int main()
{
	RankingBoard rank;
	try {
		rank.load("MonsterWorld.rnk");
	}
	catch (FileException e) {
		string passwd, correct = "123456";
		cout << "랭킹 파일이 없습니다. 관리자 암호를 입력하세요: ";
		
        char ch;
        while ((ch = getch()) != '\r' && ch != '\n') {
            passwd += ch;
            cout << '*';
        }
        cout << endl;

		if (passwd != correct) {
			cout << "암호가 틀렸습니다.\n\n";
			exit(0);
		}
		cout << "기본 랭킹 파일이 생성됩니다." << endl;
        rank.store("MonsterWorld.rnk");
	}
	rank.print("[현재 랭킹: 시작 전]");

	srand((unsigned int)time(NULL));
	int w = 20, h = 10;

	MonsterWorld game(w, h);
	game.add(new Zombie("허접좀비", "Z", rand() % w, rand() % h));
	game.add(new Vampire("뱀파이어", "V", rand() % w, rand() % h));
	game.add(new KGhost("처녀귀신", "G", rand() % w, rand() % h));
	game.add(new Jiangshi("강시(좌우)", "J", rand() % w, rand() % h, true));
	game.add(new Jiangshi("강시(상하)", "j", rand() % w, rand() % h, false));

	Human* player_left = new Human("좌", "<-", 0, h / 2, WASD);
	Human* player_right = new Human("우", "->", w - 1, h / 2, IJKL);
	game.add(player_left);
	game.add(player_right);

	game.play(500, 100);

    Human* winner = nullptr;
    if (player_right->getNItem() > player_left->getNItem()) {
        winner = player_right;
    } else if (player_left->getNItem() > player_right->getNItem()) {
        winner = player_left;
    }
    else { 
        double eff_left = (player_left->getTotalMove() == 0) ? 0 : player_left->getNItem() / player_left->getTotalMove();
        double eff_right = (player_right->getTotalMove() == 0) ? 0 : player_right->getNItem() / player_right->getTotalMove();
        if (eff_right > eff_left) winner = player_right;
        else winner = player_left; 
    }

    if (winner != nullptr && winner->getNItem() > 0) {
        double efficiency = (winner->getTotalMove() == 0) ? 0 : winner->getNItem() / winner->getTotalMove();
	    rank.add(winner->getNItem(), efficiency);
    }

	rank.print("[게임 랭킹: 최종]");
	
    // #############################################################
    // ##                  여기에 코드가 추가되었습니다                  ##
    // #############################################################

	try {
        // 기본 파일 이름으로 랭킹 저장을 시도합니다.
		rank.store("MonsterWorld.rnk");
        cout << "MonsterWorld.rnk 파일에 랭킹을 성공적으로 저장했습니다." << endl;
	}
	catch (FileException e) {
        // 파일 저장 실패 시 예외를 처리합니다.
		string passwd, correct = "123456";
		cout << "\n오류: '" << e.filename << "' 파일에 랭킹을 저장할 수 없습니다." << endl;
        cout << "파일 권한 등을 확인하거나 관리자 암호를 입력하여 다른 이름으로 저장하세요." << endl;
		cout << "관리자 암호: ";
		
        char ch;
        while ((ch = getch()) != '\r' && ch != '\n') {
            passwd += ch;
            cout << '*';
        }
        cout << endl;

        // 1. 비밀번호가 틀리면 메시지를 출력하고 프로그램을 종료합니다.
		if (passwd != correct) {
			cout << "암호가 틀렸습니다. 저장을 취소하고 프로그램을 종료합니다.\n\n";
			exit(0);
		}
        // 2. 비밀번호가 맞으면 새로운 파일 이름을 입력받아 저장합니다.
		else {
			string newFilename;
			cout << "암호가 확인되었습니다. 랭킹을 저장할 새 파일 이름을 입력하세요: ";
			cin >> newFilename;
			try {
                // 새로운 파일 이름으로 다시 저장을 시도합니다.
				rank.store(newFilename);
				cout << "'" << newFilename << "'에 랭킹을 성공적으로 저장했습니다." << endl;
			}
			catch (FileException e2) {
                // 두 번째 시도도 실패하면 오류 메시지를 출력하고 종료합니다.
				cout << "\n오류: '" << e2.filename << "' 파일에도 저장을 실패했습니다. 프로그램을 종료합니다." << endl;
			}
		}
	}
}