#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

struct shared {
    char sel[100];
    int b;
};

void home_process(int shm_id, int pipe_fd[2]) {
    struct shared *shm_ptr;
    char selection;
    
    shm_ptr = (struct shared *) shmat(shm_id, NULL, 0);
    
    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");
    scanf(" %c", &selection);
    
    strcpy(shm_ptr->sel, &selection);
    shm_ptr->b = 1000;
    
    printf("Your selection: %c\n\n", selection);
    
    // Sending data to opr_process
    close(pipe_fd[0]); 
    write(pipe_fd[1], "Data Ready", sizeof("Data Ready"));
    close(pipe_fd[1]); 
    
    wait(NULL);
    
    shmctl(shm_id, IPC_RMID, NULL);
}

void opr_process(int shm_id, int pipe_fd[2]) {
    struct shared *shm_ptr;
    int amount;
    char buf[100];
    
    shm_ptr = (struct shared *) shmat(shm_id, NULL, 0);
    
    if (shm_ptr == (struct shared *) -1) {
        perror("shmat");
        exit(1);
    }
    
    // Waiting for data from home process
    close(pipe_fd[1]);  
    read(pipe_fd[0], buf, sizeof(buf));
    close(pipe_fd[0]); 
    
    char type = shm_ptr->sel[0];
    
    if (type == 'a') {
            printf("Enter amount to be added:\n");
            scanf("%d", &amount);
            
            if (amount > 0) {
                shm_ptr->b += amount;
                printf("Balance added successfully\n");
                printf("Updated balance after addition: %d\n", shm_ptr->b);
                printf("Thank you for using\n");
            } 
            
            else {
                printf("Adding failed, Invalid amount\n");
                printf("Thank you for using\n");
            }
            
    }

    else if (type == 'w') {
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &amount);
            
            if (amount > 0 && amount <= shm_ptr->b) {
                shm_ptr->b -= amount;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal: %d\n", shm_ptr->b);
                printf("Thank you for using\n");
            } 
            
            else {
                printf("Withdrawal failed, Invalid amount\n");
                printf("Thank you for using\n");
            }
         
    }
    
    else if (type == 'c') {
            printf("Your current balance is: %d\n", shm_ptr->b);
            printf("Thank you for using\n");
    }
    
    else {
            printf("Invalid selection\n");
            printf("Thank you for using\n");
    }
   
    
    // Write message to parent process
    close(pipe_fd[0]);  
    write(pipe_fd[1], "Thank you for using", sizeof("Thank you for using"));
    close(pipe_fd[1]); 
    
    shmctl(shm_id, IPC_RMID, NULL);
    
    exit(0);
}

int main() {
    int shm_id;
    int pipe_fd[2];
    pid_t pid;
    
    shm_id = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmid not found");
        exit(1);
    }
    
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    } 
    else if (pid == 0) {
        opr_process(shm_id, pipe_fd);
    } 
    else {
        home_process(shm_id, pipe_fd);
    }
    
    return 0;
}

