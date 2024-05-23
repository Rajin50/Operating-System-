#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork(); 
    
    if (child_pid < 0) { 
        printf("Fork failed\n");
        return 1;
    } 
    
    else if (child_pid == 0) { 
        pid_t grandchild_pid = fork(); 
        
        if (grandchild_pid < 0) { 
            printf("Fork failed\n");
            return 1;
        } 
        
        else if (grandchild_pid == 0) { 
            printf("I am grandchild\n");
            exit(0); 
        }
        
        wait(NULL); 
        printf("I am child\n"); 
        exit(0); 
    } 
    
    else { 
        wait(NULL); 
        printf("I am parent\n"); 
    }
    return 0;
}


