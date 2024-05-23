#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>

struct msg {
    long int type;
    char txt[6];
};

int main() {
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgid not found");
        exit(1);
    }

    pid_t otp_pid = fork();

    if (otp_pid == -1) {
        printf("fork failed\n");
        exit(1);
    } 
    
    else if (otp_pid == 0) {
        struct msg message;
        struct msg otp_msg;

        msgrcv(msgid, &message, sizeof(message.txt), 1, 0);
        printf("OTP generator received workspace name from log in: %s\n\n", message.txt);

        snprintf(otp_msg.txt, sizeof(otp_msg.txt), "%d", getpid());
        otp_msg.type = 2;

        msgsnd(msgid, &otp_msg, sizeof(otp_msg.txt), 0);
        printf("OTP sent to log in from OTP generator: %s\n", otp_msg.txt);

        otp_msg.type = 3;
        msgsnd(msgid, &otp_msg, sizeof(otp_msg.txt), 0);
        printf("OTP sent to mail from OTP generator: %s\n", otp_msg.txt);

        exit(0);
    } 
    
    else {
        pid_t mail_pid = fork();

        if (mail_pid == -1) {
            printf("fork failed\n");
            exit(1);
        } 
        
        else if (mail_pid == 0) {
            struct msg rcv_otp;
            struct msg mail_msg;

            msgrcv(msgid, &rcv_otp, sizeof(rcv_otp.txt), 3, 0);
            printf("Mail received OTP from OTP generator: %s\n", rcv_otp.txt);

            snprintf(mail_msg.txt, sizeof(mail_msg.txt), "%s", rcv_otp.txt);
            mail_msg.type = 4;
            msgsnd(msgid, &mail_msg, sizeof(mail_msg.txt), 0);
            printf("OTP sent to log in from mail: %s\n", mail_msg.txt);

            exit(0);
        } 
        
        else {
            struct msg message;
            struct msg rcv_otp;

            printf("Please enter the workspace name:\n");
            scanf("%s", message.txt);

            if (strcmp(message.txt, "cse321") != 0) {
                printf("Invalid workspace name\n");
                exit(1);
            }
            
            message.type = 1;
            msgsnd(msgid, &message, sizeof(message.txt), 0);
            printf("Workspace name sent to otp generator from log in: %s\n\n", message.txt);

            wait(NULL);
            msgrcv(msgid, &rcv_otp, sizeof(rcv_otp.txt), 2, 0);
            printf("Log in received OTP from OTP generator: %s\n", rcv_otp.txt);

            msgrcv(msgid, &rcv_otp, sizeof(rcv_otp.txt), 4, 0);
            printf("Log in received OTP from mail: %s\n", rcv_otp.txt);

            if (strcmp(rcv_otp.txt, rcv_otp.txt) == 0) {
                printf("OTP Verified\n");
            } 
            
            else {
                printf("OTP Incorrect\n");
            }

            msgctl(msgid, IPC_RMID, NULL);

            wait(NULL);
        }
    }

    return 0;
}
