#include "p147_No.05_header.h"

int playRussianRoulette(int nTurns, int nBullets, int nChambers) {
    int start = rand() % nTurns; // 시작 플레이어 랜덤 선택
    printf("\nI spun the gun. We start from No%d\n", start + 1);
    
    int bulletsLeft = nBullets;
    int chambers[nChambers];
    
    // 탄창 초기화 (총알 배치)
    for (int i = 0; i < nChambers; i++) {
        chambers[i] = (i < nBullets) ? 1 : 0;
    }
    
    // 탄창을 랜덤하게 섞기
    for (int i = nChambers - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = chambers[i];
        chambers[i] = chambers[j];
        chambers[j] = temp;
    }
    
    int chamberIndex = 0;
    while (bulletsLeft > 0) {
        printf("No%d's turn. Press Enter to pull the trigger...", start + 1);
        getchar();
        
        if (chambers[chamberIndex] == 1) {
            printf("\tBang!!!!!! No%d is dead...\n", start + 1);
            bulletsLeft--;
        } else {
            printf("\tOh God... I survived\n");
        }
        
        chamberIndex++;
        start = (start + 1) % nTurns; // 다음 플레이어로 이동
    }
    
    printf("\nAll bullets have been fired. The game is over.\n");
    return 0;
}

int main() {
    int nTurns, nBullets, nChambers;
    srand((unsigned)time(NULL));

    printf("Number of players: ");
    scanf("%d", &nTurns);
    
    printf("Number of chambers in the revolver: ");
    scanf("%d", &nChambers);
    
    printf("Number of bullets (must be <= chambers): ");
    scanf("%d", &nBullets);
    getchar(); // 버퍼 정리

    if (nBullets > nChambers) {
        printf("Invalid input: Number of bullets cannot exceed chambers.\n");
        return 1;
    }

    playRussianRoulette(nTurns, nBullets, nChambers);
    return 0;
}
