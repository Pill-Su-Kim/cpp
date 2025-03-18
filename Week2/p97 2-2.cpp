#include <stdio.h>
#include <vector>

using namespace std;



const char* unitKorean[] = {"", "십", "백", "천", "만"}; //I got this solution from Chat gpt

void CTK(int num) {
    if (num == 0) {
        printf("영\n");
        return;
    }

    vector<int> digits;  // I got this solution from Chat gpt(16~21)

    while (num > 0) {
        digits.push_back(num % 10); 
        num /= 10;
    }

    int len = digits.size();  
    bool needPrint = false;   

    for (int i = len - 1; i >= 0; i--) {
        int digit = digits[i];  

       
        if (digit == 0) continue;

       
        if (needPrint && i == 4) printf("만");

        
        printf("%i", digits);

        
        if (i > 0) printf("%s", unitKorean[i]);

        needPrint = true;
    }

    printf("\n"); 
}

int main() {
    int number;
    printf("숫자를 입력하세요: ");
    scanf("%d", &number);
    CTK(number);

    return 0;
}
