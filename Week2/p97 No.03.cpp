#include <cstdio>
#include <cmath>


double approximatePi(int terms) {
    double pi = 0.0;
    for (int i = 0; i < terms; ++i) {
       
        pi += pow(-1, i) / (2 * i + 1); 
    }
    return 4 * pi;  
}

int main() {
    int n;
    printf("정수 n을 입력하세요 (계산할 항의 수): ");
    scanf("%d", &n);  

    double pi_approx = approximatePi(n);
    printf("π에 대한 근사값: %.15f\n", pi_approx);  

    return 0;
}
