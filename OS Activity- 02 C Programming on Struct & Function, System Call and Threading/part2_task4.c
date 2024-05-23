#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] < arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

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

    pid_t pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
        return 1;
    } 
    
    else if (pid == 0) {
        bubbleSort(arr, n);
        printf("Sorted array in descending order: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } 
    
    else {
        wait(NULL); 
        printOddEven(arr, n);
    }

    return 0;
}
