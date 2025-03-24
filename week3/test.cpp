#include "p147_No.05_header.h"

int playRussianRullet(int nturns, int nBullets){

    int start = rand() % nturns;
    printf("\nI spun the guns We start from No%d\n", start +1);
    while(true){
        int pos = rand() %6;
        printf("%dtimes\t We spun the bullet randomly\n", start +1);
        printf("\t Press Enter to fire!!!");
        getchar();
        if (pos < nBullets) break;
        printf("\t Oh God... I have survived\n");
        start = (start +1)% nturns;


    }

    printf("\tBang!!!!!!\n");
    return start +1;

}

int main(){
    int nturns, nBullets;
    srand((unsigned)time(NULL));

    printf("game people(ex:2):");
    scanf("%d", &nturns);
    printf("the number of bullets(under 6):");
    scanf("%d", &nBullets);
    getchar();

    int bang = playRussianRullet(nturns, nBullets);
    printf("\n > No%d attender is dead...\n", bang);
    
}