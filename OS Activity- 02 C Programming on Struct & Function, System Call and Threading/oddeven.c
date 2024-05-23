#include <stdio.h>
#include <stdlib.h>

void printOddEven(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            printf("%d is even\n", arr[i]);
        else
            printf("%d is odd\n", arr[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("%s \n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int arr[n];

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i+1]);
    }

    printOddEven(arr, n);

    return 0;
}
