#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int a, b, c;
    int count = 1;
   
    a = fork();
    if (a < 0) {
        printf("fork failed\n");
        return 1;
    } 
    
    else if (a == 0) {
        if (getpid() % 2 != 0) {
            b = fork();
            if (b < 0) {
                printf("fork failed\n");
                return 1;
            } 
            
            else if (b == 0) {
                if (getpid() % 2 != 0) {
                    c = fork();
                    if (c < 0) {
                        printf("fork failed\n");
                        return 1;
                    } 
                    
                    else if (c == 0) {
                        count++;
                    }
                }
            }
        }
    } 
    
    else {
        count++;
        wait(NULL); 
    }

    printf("Number of processes created: %d\n", count);

    return 0;
}

