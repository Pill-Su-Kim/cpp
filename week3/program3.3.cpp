#include<stdio.h>
int factorial(int);
int add(int, int);
int main(){
    int x = 3,y=4, z;
    z= add(x, y); // There is no datatype of function add,  so I just declared function add and including int next to add and including (int, int), There is no problem about starting program
    printf("x + y = %d\n", z);
    printf("x + y = %d\n", add(x, 10));
    printf("5+10 = %d\n", add(5, 100));

    z = factorial(x);
    printf("%d! = %d\n", x,z);
    printf("5! = %d\n", factorial(5));


}