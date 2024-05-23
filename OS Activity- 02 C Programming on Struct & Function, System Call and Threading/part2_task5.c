#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t parent_pid = getpid(); 

    printf("1. Parent process ID: %d\n", parent_pid); 

    pid_t child_pid = fork(); 

    if (child_pid < 0) { 
        printf("fork failed\n");
        return 1;
    } 
    
    else if (child_pid == 0) { 
    	printf("2. Child process ID: %d\n", getpid());
        pid_t grandchild1_pid = fork(); 

        if (grandchild1_pid < 0) { 
            printf("fork failed\n");
            return 1;
        } 
        
        else if (grandchild1_pid == 0) { 
            printf("3. Grandchild process ID: %d\n", getpid()); 
        } 
        
        else { 
            pid_t grandchild2_pid = fork(); 
            if (grandchild2_pid < 0) { 
                printf("fork failed\n");
                return 1;
            } 
            
            else if (grandchild2_pid == 0) { 
                printf("4. Grandchild process ID: %d\n", getpid()); 
            } 
            
            else { 
                pid_t grandchild3_pid = fork(); 

                if (grandchild3_pid < 0) { 
                    printf("fork failed\n");
                    return 1;
                } 
                
                else if (grandchild3_pid == 0) { 
                    printf("5. Grandchild process ID: %d\n", getpid()); 
                }
            }
        }
    } 
    
    else { 
        wait(NULL); 
    }
    return 0;
}



