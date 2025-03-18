#include <stdio.h>
int main()
{
	int income;
	double tax = 0;
	printf("������ �Է��ϼ��� ==> ");
	scanf("%d", &income);

	if (income <= 1200) {
		tax = income * 0.06;
	}
	if (1200<income  && income <= 4600) {
		tax = 1200 * 0.06 + (income - 1200) * 0.15;
	}
	if (4600<income  && income <= 8800) {
		tax = 1200 * 0.06 + (4600 - 1200)* 0.15 + (income - 4600)*0.24;
	}
	if (8800<income  && income <= 15000) {
		tax = 1200 * 0.06 + (4600 - 1200)* 0.15 + (8800 - 4600)*0.24 + (income - 8800)*0.35;
	}
	if (15000 < income) {
		tax = 1200 * 0.06 + (4600 - 1200)* 0.15 + (8800 - 4600)*0.24 + (15000 - 8800)*0.35 + (income - 15000)*0.38;
	}
	printf(" ��ü������ %7.1f�����Դϴ�.\n", tax);
	printf(" �����ҵ��� %7.1f�����Դϴ�.\n", income - tax);
}