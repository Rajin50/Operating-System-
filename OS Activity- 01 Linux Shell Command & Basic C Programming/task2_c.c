#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool has_lowercase(char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (islower(password[i]))
            return true;
    }
    return false;
}

bool has_uppercase(char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i]))
            return true;
    }
    return false;
}

bool has_digit(char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (isdigit(password[i]))
            return true;
    }
    return false;
}

bool has_special(char *password) {
    char special_chars[] = {'_', ',', '$', '#', '@'};
    for (int i = 0; password[i] != '\0'; i++) {
        for (int j = 0; j < strlen(special_chars); j++) {
            if (password[i] == special_chars[j])
                return true;
        }
    }
    return false;
}

int main() {
    char password[50];
    printf("Enter your password: ");
    scanf("%s", password);

    bool lowercase = has_lowercase(password);
    bool uppercase = has_uppercase(password);
    bool digit = has_digit(password);
    bool special = has_special(password);
    
    if (!uppercase && !digit && !special)
    	printf("Uppercase character missing, Digit missing, Special character missing\n");
    else if (!lowercase)
        printf("Lowercase character missing\n");
    else if (!uppercase)
        printf("Uppercase character missing\n");
    else if (!digit)
        printf("Digit missing\n");
    else if (!special)
        printf("Special character missing\n");
    else if (lowercase && uppercase && digit && special)
        printf("OK\n");

    return 0;
}
