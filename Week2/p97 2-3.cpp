#include <stdio.h>
#include <vector>

using namespace std;


const char* unitKorean[] = {"", "십", "백", "천", "만"};

void convertToKorean(int num) {
    if (num == 0) {
        printf("영\n");
        return;
    }

    vector<int> digits;  

    while (num > 0) {
        digits.push_back(num % 10); 
        num /= 10;
    }

    int len = digits.size();  
    bool needPrint = false;   

    for (int i = len - 1; i >= 0; i--) {
        int digit = digits[i];  
        if (digit > 0) {
            
            if (digit == 1 && (i > 0)) {
                printf("%s", unitKorean[i]);
            } else {
                printf("%d", digit);  
                if (i > 0) printf("%s", unitKorean[i]); 
            }
            needPrint = true;
        } else if (needPrint && i == 4) {
            printf("만"); 
        }
    }

    printf("\n");
}

int main() {
    int number;
    printf("숫자를 입력하세요: ");
    scanf("%d", &number);
    convertToKorean(number);

    return 0; 
}

