#include <stdio.h>
#include <string.h>

int isEmailUpdated(char *email) {
    // Check if the email contains "@kaaj.com" or "sheba.xyz"
    if (strstr(email, "@kaaj.com") != NULL) 
        return 0; 
    else if (strstr(email, "@sheba.xyz") != NULL) 
        return 1; 
        
    return -1;
}

int main() {
    char email[100];

    printf("Enter the email address: ");
    scanf("%s", email);

    int updated = isEmailUpdated(email);
    
    if (updated == 0) 
        printf("Email address is outdated\n");
    else if (updated == 1) 
        printf("Email address is okay\n");
    else 
        printf("Invalid email address\n");

    return 0;
}

