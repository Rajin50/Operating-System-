#include <stdio.h>
int main() {
	int a;
	int b;
	printf("Enter the first number: ");
	scanf("%d", &a);
	printf("Enter the second number: ");
	scanf("%d", &b);
	
	if (a > b) {
		int p;
		p = a - b;
		printf("The result of substruction is: %d \n", p);
	}
	
	else if (a < b) {
		int p;
		p = a + b;
		printf("The result of addition is: %d \n", p);
	}
	
	else {
		int p;
		p = a * b;
		printf("The result of multiplication is: %d \n", p);
	}
	return 0;
}
