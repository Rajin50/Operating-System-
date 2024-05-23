#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    char name[100];
    int sum;
} ThreadArgs;

int AsciiSum(char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    return sum;
}

void *SumThread(void *args) {
    ThreadArgs *threadArgs = (ThreadArgs *)args;
    threadArgs->sum = AsciiSum(threadArgs->name);
    pthread_exit(NULL);
}

void *ResultsThread(void *args) {
    ThreadArgs *threadArgs = (ThreadArgs *)args;
    
    if (threadArgs[0].sum == threadArgs[1].sum && threadArgs[1].sum == threadArgs[2].sum) {
        printf("Youreka\n");
    } 
    
    else if (threadArgs[0].sum == threadArgs[1].sum || threadArgs[0].sum == threadArgs[2].sum || threadArgs[1].sum == threadArgs[2].sum) {
        printf("Miracle\n");
    } 
    
    else {
        printf("Hasta la vista\n");
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4]; 
    ThreadArgs threadArgs[3]; 

    char names[3][100] = {"Rajin", "Shakib", "Mashrafee"};

    for (int i = 0; i < 3; i++) {
        strcpy(threadArgs[i].name, names[i]); 
        pthread_create(&threads[i], NULL, SumThread, &threadArgs[i]); 
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_create(&threads[3], NULL, ResultsThread, threadArgs);
    pthread_join(threads[3], NULL);

    return 0;
}
