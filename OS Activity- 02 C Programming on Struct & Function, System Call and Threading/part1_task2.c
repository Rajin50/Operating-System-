#include <stdio.h>
int isPerfect(int num) {
    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum == num;
}

void Perfect_Nums(int s, int e) {
    for (int i = s; i <= e; i++) {
        if (isPerfect(i)) {
            printf("%d\n", i);
        }
    }
}

int main() {
    int s, e;

    printf("Enter the start num: ");
    scanf("%d", &s);
    printf("Enter the end num: ");
    scanf("%d", &e);

    Perfect_Nums(s, e);

    return 0;
}
